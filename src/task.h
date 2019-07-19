#ifndef TASK_H
#define TASK_H

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
private:
    char id;

public:
    char condition;
    char state;
    char event;
    int timer;
    char sem;
    int* semaphores;
};

#endif