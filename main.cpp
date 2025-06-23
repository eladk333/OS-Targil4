#include <iostream>
#include <pthread.h>
#include "BoundedBuffer.h"
#include "Producer.h"
#include "Dispatcher.h"
#include "CoEditor.h"
#include "ScreenManager.h"
#include "ConfigParser.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./ex4.out <config_file>" << std::endl;
        return 1;
    }

    Config config = parse_config(argv[1]);
    int numProducers = config.producers.size();

    // Debug output for config
    // std::cout << "Parsed config: " << numProducers << " producers, co-editor queue size = "
    //           << config.coEditorQueueSize << std::endl;
    // for (const auto& p : config.producers) {
    //     std::cout << "Producer " << p.id << ": " << p.messageCount << " messages, queue size = "
    //               << p.queueSize << std::endl;
    // }

    // --- Create producer queues
    std::vector<BoundedBuffer*> producerQueues;
    std::vector<ProducerArgs*> producerArgs;
    std::vector<pthread_t> producerThreads(numProducers);

    for (int i = 0; i < numProducers; ++i) {
        BoundedBuffer* queue = new BoundedBuffer(config.producers[i].queueSize);
        producerQueues.push_back(queue);

        ProducerArgs* args = new ProducerArgs{
            config.producers[i].id,
            config.producers[i].messageCount,
            queue
        };
        producerArgs.push_back(args);

        pthread_create(&producerThreads[i], nullptr, producer_thread, args);
    }

    // --- Create dispatcher queues (S/N/W)
    BoundedBuffer* sportsQueue = new BoundedBuffer(100);
    BoundedBuffer* newsQueue = new BoundedBuffer(100);
    BoundedBuffer* weatherQueue = new BoundedBuffer(100);

    DispatcherArgs dispatcherArgs {
        producerQueues, sportsQueue, newsQueue, weatherQueue
    };
    pthread_t dispatcherThread;
    pthread_create(&dispatcherThread, nullptr, dispatcher_thread, &dispatcherArgs);

    // --- Create CoEditor output queue
    BoundedBuffer* coEditorOutputQueue = new BoundedBuffer(config.coEditorQueueSize);

    // --- Create CoEditor threads
    CoEditorArgs coEditorArgs[3] = {
        {sportsQueue, coEditorOutputQueue},
        {newsQueue, coEditorOutputQueue},
        {weatherQueue, coEditorOutputQueue}
    };

    pthread_t coEditorThreads[3];
    for (int i = 0; i < 3; ++i) {
        pthread_create(&coEditorThreads[i], nullptr, co_editor_thread, &coEditorArgs[i]);
    }

    // --- Create screen manager thread
    ScreenManagerArgs screenArgs {coEditorOutputQueue};
    pthread_t screenThread;
    pthread_create(&screenThread, nullptr, screen_manager_thread, &screenArgs);

    // --- Join all threads
    for (int i = 0; i < numProducers; ++i) {
        pthread_join(producerThreads[i], nullptr);
    }
    pthread_join(dispatcherThread, nullptr);
    for (int i = 0; i < 3; ++i) {
        pthread_join(coEditorThreads[i], nullptr);
    }
    pthread_join(screenThread, nullptr);

    // --- Clean up dynamically allocated memory
    for (int i = 0; i < numProducers; ++i) {
        delete producerQueues[i];
        delete producerArgs[i];
    }
    delete sportsQueue;
    delete newsQueue;
    delete weatherQueue;
    delete coEditorOutputQueue;

    return 0;
}
