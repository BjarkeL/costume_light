#include "task.h"

#include "definitions.h"

Task::Task() {

}

Task::~Task() {
    
}

int Task::run_task(char _state) {
    return 0;
}

void Task::update_task() {
    // Count down the timer:
    if (condition == TASK_WAITING_FOR_TIMEOUT) {
        if (!(--timer)) {
            condition = TASK_READY;
            event = TIMEOUT_EVENT;
        }
    }

    if (condition == TASK_WAITING_FOR_SEMAPHORE) {
        if (sem_wait(sem))
            event = SIGNAL_EVENT;
    }

    if (condition == TASK_READY) {
        run_task(state);
    }
}

void Task::set_id(char _id) {
    id = _id;
}

char Task::get_id() {
    return id;
}

void Task::wait(int _time) {
    timer = _time;
    condition = TASK_WAITING_FOR_TIMEOUT;
}

void Task::sem_signal(char _sem) {
    if (_sem < MAX_SEMAPHORES) {
        semaphores[_sem]++;
    }
}

char Task::sem_wait(char _sem) {
    char result = 0;
    if (_sem < MAX_SEMAPHORES) {
        if (semaphores[_sem]) {
            semaphores[_sem]--;
            condition = TASK_READY;
            result = 1;
        } else {
            sem = _sem;
            condition = TASK_WAITING_FOR_SEMAPHORE;
        }
    }
    return result;
}