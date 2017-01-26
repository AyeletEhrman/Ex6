//
// Created by riki on 25/01/17.
//

#ifndef EX6_TASK_H
#define EX6_TASK_H


class Task {
    private:
        void *arg;
        void *(*func)(void *arg);
    public:
        Task(void* (*func1)(void *arg1), void* arg1);
        virtual ~Task();
        void execute();
};

#endif //EX6_TASK_H
