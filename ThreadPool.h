
#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include "Task.h"
#include "Trip.h"
#include <queue>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
using namespace std;
/**
 * a thread pool class that will manage few threads.
 */
class ThreadPool {
    private:
        int threadsNum;
        vector<pthread_t>* threads;
        bool stop;
        queue<Task*>* tasksQueue;
        pthread_mutex_t lock;
    public:
        /**
         * a constructor of thread pool.
         * @param threads_num
         * @return thread pool object
         */
        ThreadPool(int threads_num);
        /**
         * a default constructor of thread pool.
         * @param threads_num
         * @return thread pool object
         */
        ThreadPool() {};
        /**
         * a distructor of thread pool
         */
        virtual ~ThreadPool();
         /**
         * a method to do all tasks of threads
         */
        void doTasks();
        /**
         * a method to add a task to the pool.
         * @param task
         */
        void addTask(Task* task);
        /**
         * a method to make all the threads of the pool terminate.
         */
        void terminate();
};

#endif /* THREADPOOL_H_ */