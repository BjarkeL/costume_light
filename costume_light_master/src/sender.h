#ifndef SENDER_H
#define SENDER_H

#include "task.h"
#include "Wire.h"
#include "definitions.h"

#define SENDER_INIT 0
#define SENDER_READY 1

class Sender: public Task {
public:
    Sender();

    void sender_init();
    int run_task(char _state);
private:
    char frame_counter = 0;
};

#endif