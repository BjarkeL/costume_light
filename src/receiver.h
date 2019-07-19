#ifndef RECEIVER_H
#define RECEIVER_H

#include "task.h"
#include "Wire.h"
#include "avr/io.h"

#define RECEIVER_INIT 0
#define RECEIVER_READY 1

#define RECEIVER_ID 8

class Receiver: public Task {
public:
    Receiver();

    void receiver_init();
    int run_task(char _state);
private:
    static void receive_event();
};

#endif