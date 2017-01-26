
#ifndef THREADPOOL_H_
#define THREADPOOL_H_

#include "Task.h"
#include "Trip.h"
#include <queue>
#include <pthread.h>
using namespace std;

class ThreadPool {
    private:
        int threadsNum;
        //int currId;
        vector<pthread_t>* threads;
        bool stop;
        queue<Task*>* tasksQueue;
        pthread_mutex_t lock;
    public:
        ThreadPool(int threads_num);
        ThreadPool() {};
        virtual ~ThreadPool();
        void doTasks();
        void addTask(Task* task);
        void terminate();
};

#endif /* THREADPOOL_H_ */