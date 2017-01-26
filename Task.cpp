//
// Created by riki on 25/01/17.
//

#include "Task.h"

Task::Task(void *(*func1)(void *arg1), void *arg1) {
    func = func1;
    arg = arg1;
}

Task::~Task() {
}

void Task::execute() {
    func(arg);
}
