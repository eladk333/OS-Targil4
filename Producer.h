#ifndef PRODUCER_H
#define PRODUCER_H

#include "BoundedBuffer.h"
#include <string>
#include <vector>

struct ProducerArgs {
    int id;
    int messageCount;
    BoundedBuffer* queue;
};

void* producer_thread(void* arg);

#endif
