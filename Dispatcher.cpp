#include "Dispatcher.h"
#include <unistd.h>

void* dispatcher_thread(void* arg) {
    DispatcherArgs* args = static_cast<DispatcherArgs*>(arg);
    int doneCount = 0;
    int numProducers = args->producerQueues.size();
    std::vector<bool> producerDone(numProducers, false);

    while (doneCount < numProducers) {
        for (int i = 0; i < numProducers; ++i) {
            if (producerDone[i]) continue;

            std::string msg = args->producerQueues[i]->remove();

            if (msg == "DONE") {
                producerDone[i] = true;
                doneCount++;
            } else if (msg.find("SPORTS") != std::string::npos) {
                args->sportsQueue->insert(msg);
            } else if (msg.find("NEWS") != std::string::npos) {
                args->newsQueue->insert(msg);
            } else if (msg.find("WEATHER") != std::string::npos) {
                args->weatherQueue->insert(msg);
            }
        }
        usleep(1000); // short sleep to avoid tight loop
    }

    args->sportsQueue->insert("DONE");
    args->newsQueue->insert("DONE");
    args->weatherQueue->insert("DONE");

    return nullptr;
}
