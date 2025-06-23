#include "BoundedBuffer.h"
#include <iostream>
#include <unistd.h>

BoundedBuffer::BoundedBuffer(int size) : capacity(size) {
    sem_init(&empty, 0, size);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, nullptr);
}

BoundedBuffer::~BoundedBuffer() {
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
}

void BoundedBuffer::insert(const std::string& item) {
    sem_wait(&empty);
    pthread_mutex_lock(&mutex);
    buffer.push(item);
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
}

std::string BoundedBuffer::remove() {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    std::string item = buffer.front();
    buffer.pop();
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    return item;
}
