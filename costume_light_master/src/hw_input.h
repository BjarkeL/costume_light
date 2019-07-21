#ifndef HW_INPUT_H
#define HW_INPUT_H

#include "task.h"
#include "avr/io.h"
#include "definitions.h"

#define HW_INIT 0
#define HW_READY 1

#define PLAY_BUTTON_PIN 5
#define ON_BUTTON_PIN 6
#define CYCLE_ANIMATION_BUTTON_PIN 7

class HwInput: public Task {
public:
    HwInput();

    void hw_init();
    int run_task(char _state);
private:

};

#endif