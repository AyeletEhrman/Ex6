
#ifndef EX6_TASK_H
#define EX6_TASK_H

/**
 * a Task class built with function and arg to it
 */
class Task {
    private:
        void *arg;
        void *(*func)(void *arg);
    public:
        /**
         * a constructor for task
         * @param func1
         * @param arg1
         * @return Task object
         */
        Task(void* (*func1)(void *arg1), void* arg1);
        /**
         * a contructor for task
         */
        virtual ~Task();
        /**
         * a method that runs the function of task
         */
        void execute();
};

#endif //EX6_TASK_H
