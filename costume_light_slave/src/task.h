#ifndef TASK_H
#define TASK_H

#include "definitions.h"

typedef struct {
    char status;
    int time;
} timer;

class Task {
public:
    Task();
    ~Task();

    virtual int run_task(char _state);
    void update_task();

    void set_id(char _id);
    char get_id();

    void wait(int _time);
    void sem_signal(char _sem);
    char sem_wait(char _sem);
    char sem_check(char _sem);

    void set_timer(char _id, int _time);
    char check_timer(char _id);
    void reset_timer(char _id);
    static void update_timers();
private:
    char id;

    static timer timers[MAX_TIMERS];
    static int semaphores[MAX_SEMAPHORES];

public:
    char condition;
    char state;
    char event;
    int timer;
    char sem;
};

#endif