#ifndef BOUNDED_BUFFER_H
#define BOUNDED_BUFFER_H

#include <semaphore.h>
#include <queue>
#include <string>
#include <pthread.h>

class BoundedBuffer {
private:
    std::queue<std::string> buffer;
    int capacity;

    sem_t empty;
    sem_t full;
    pthread_mutex_t mutex;

public:
    BoundedBuffer(int size);
    ~BoundedBuffer();

    void insert(const std::string& item);
    std::string remove();
};

#endif
