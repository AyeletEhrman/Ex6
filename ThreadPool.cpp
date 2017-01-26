#include "ThreadPool.h"
/**
 * static function to send to the thread.
 * @param arg
 * @return NULL
 */
static void *startTasks(void *arg) {
    ThreadPool* pool = (ThreadPool*)arg;
    // do all pool tasks.
    pool->doTasks();
    return NULL;
}

ThreadPool::ThreadPool(int threadsN) {
    threadsNum = threadsN;
    stop = false;
    threads = new vector<pthread_t>(threadsNum);
    tasksQueue = new queue<Task*>;
    pthread_mutex_init(&lock, NULL);
    // create all the wanted threads.
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
        // check if we got a task to do.
        if (!tasksQueue->empty()) {
            Task* task = tasksQueue->front();
            tasksQueue->pop();
            pthread_mutex_unlock(&lock);
            // execute the task function.
            task->execute();
            delete task;
        } else {
            pthread_mutex_unlock(&lock);
            sleep(1);
        }
    }
}

void ThreadPool::addTask(Task* task) {
    tasksQueue->push(task);
}

void ThreadPool::terminate() {
    // cancel all the threads.
    for (int i = 0; i < threadsNum; i++) {
        pthread_cancel(threads->at(i));
    }
    stop = true;
}
