#ifndef LEDS_H
#define LEDS_H

#include "task.h"
#include "avr/io.h"
#include "definitions.h"

#define LED_INIT 0
#define LED_READY 1

#define STATUS_LED 5
#define LED 4

class StatusLed: public Task {
public:
    StatusLed();

    void led_init();
    int run_task(char _state);
private:

};

class TestLed: public Task {
public:
    TestLed();

    void led_init();
    int run_task(char _state);
private:

};

#endif