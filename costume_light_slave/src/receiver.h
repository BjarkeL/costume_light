#ifndef RECEIVER_H
#define RECEIVER_H

#include "task.h"
#include "Wire.h"
#include "avr/io.h"
#include "definitions.h"

#define RECEIVER_INIT 0
#define RECEIVER_READY 1

class Receiver: public Task {
public:
    Receiver();

    void receiver_init();
    int run_task(char _state);
private:
    static void receive_event();
    static char received_val;
    static char new_msg;
};

#endif