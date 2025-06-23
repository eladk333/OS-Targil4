#ifndef CO_EDITOR_H
#define CO_EDITOR_H

#include "BoundedBuffer.h"

struct CoEditorArgs {
    BoundedBuffer* inputQueue;    // One of S/N/W dispatcher queues
    BoundedBuffer* outputQueue;   // Shared queue to screen manager
};

void* co_editor_thread(void* arg);

#endif
