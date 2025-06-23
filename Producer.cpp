#include "Producer.h"
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <unistd.h>
#include <vector>

const std::vector<std::string> TYPES = {"SPORTS", "NEWS", "WEATHER"};

void* producer_thread(void* arg) {
    ProducerArgs* args = static_cast<ProducerArgs*>(arg);
    srand(time(NULL) + args->id);

    for (int i = 0; i < args->messageCount; ++i) {
        int typeIndex = rand() % 3;
        std::ostringstream ss;
        ss << TYPES[typeIndex];  
        args->queue->insert(ss.str());
    }

    args->queue->insert("DONE");
    return nullptr;
}
