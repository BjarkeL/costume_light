#ifndef HW_INPUT_H
#define HW_INPUT_H

#include "task.h"
#include "avr/io.h"
#include "definitions.h"

#define HW_INIT 0
#define HW_READY 1

#define PLAY_BUTTON_PIN 3
#define ON_BUTTON_PIN 4

class HwInput: public Task {
public:
    HwInput();

    void hw_init();
    int run_task(char _state);
private:

};

#endif