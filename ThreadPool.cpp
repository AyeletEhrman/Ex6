#include "ThreadPool.h"
#include "Trip.h"
#include <unistd.h>
#include <iostream>

static void *startTasks(void *arg) {
    ThreadPool* pool = (ThreadPool*)arg;
    pool->doTasks();
    return NULL;
}

ThreadPool::ThreadPool(int threadsN) {
    threadsNum = threadsN;
    stop = false;
    threads = new vector<pthread_t>(threadsNum);
    tasksQueue = new queue<Task*>;
    pthread_mutex_init(&lock, NULL);
    for (int i = 0; i < threadsNum; i++) {
        pthread_create(&threads->at(i), NULL, startTasks, this);
    }
}
ThreadPool::~ThreadPool() {
    delete threads;
    // deletes the drivers.
    while (!(tasksQueue->empty())) {
        delete tasksQueue->front();
        tasksQueue->pop();
    }
    delete tasksQueue;
    pthread_mutex_destroy(&lock);
}

void ThreadPool::doTasks() {
    while (!stop) {
        pthread_mutex_lock(&lock);
        if (!tasksQueue->empty()) {

            cout << "get task" << endl;

            Task* task = tasksQueue->front();
            tasksQueue->pop();
            pthread_mutex_unlock(&lock);
            task->execute();
            delete task;
            cout << "after execute" << endl;
        }
        else {
            pthread_mutex_unlock(&lock);
            sleep(1);
        }
    }
}

void ThreadPool::addTask(Task* task) {
    tasksQueue->push(task);
}

void ThreadPool::terminate() {
    for (int i = 0; i < threadsNum; i++) {
        pthread_cancel(threads->at(i));
    }
    stop = true;
}
