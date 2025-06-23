#ifndef SCREEN_MANAGER_H
#define SCREEN_MANAGER_H

#include "BoundedBuffer.h"

struct ScreenManagerArgs {
    BoundedBuffer* inputQueue;  // Shared output queue from CoEditors
};

void* screen_manager_thread(void* arg);

#endif
