#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "BoundedBuffer.h"
#include <vector>
#include <string>

struct DispatcherArgs {
    std::vector<BoundedBuffer*> producerQueues;
    BoundedBuffer* sportsQueue;
    BoundedBuffer* newsQueue;
    BoundedBuffer* weatherQueue;
};

void* dispatcher_thread(void* arg);

#endif
