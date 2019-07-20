#include "task.h"

timer Task::timers[MAX_TIMERS] = {0};
int Task::semaphores[MAX_SEMAPHORES] = {0};

Task::Task() {

}

Task::~Task() {
    
}

int Task::run_task(char _state) {
    return 0;
}

void Task::update_task() {
    
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

char Task::sem_check(char _sem) {
    char result = 0;
    if (_sem < MAX_SEMAPHORES) {
        if (semaphores[_sem]) {
            semaphores[_sem]--;
            result = 1;
        }
    }
    return result;
}

void Task::set_timer(char _id, int _time) {
    if (_id < MAX_TIMERS) {
        timers[_id].time = _time;
        timers[_id].status = TIMER_RUNNING;
    }
}

char Task::check_timer(char _id) {
    char result = 0;
    if (_id < MAX_TIMERS) {
        result = timers[_id].status;
    }
    return result;
}

void Task::reset_timer(char _id) {
    if (_id < MAX_TIMERS) {
        timers[_id].time = 0;
        timers[_id].status = TIMER_DONE;
    }
}

void Task::update_timers() {
    for (char i = 0; i < MAX_TIMERS; i++) {
        if (timers[i].time)
            if (!(--timers[i].time))
                timers[i].status = TIMER_DONE;
    }
}