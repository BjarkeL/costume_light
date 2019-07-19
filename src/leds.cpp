#include "leds.h"

StatusLed::StatusLed() {

}

void StatusLed::led_init() {
    DDRB |= 1<<STATUS_LED;
}

int StatusLed::run_task(char _state) {
    switch(_state) {
        case LED_INIT:
            led_init();
            state = LED_READY;
            break;
        case LED_READY:
            PORTB ^= 1<<STATUS_LED;
            wait(100);
            break;
        default:
            break;
    }

    return 0;
}

TestLed::TestLed() {

}

void TestLed::led_init() {
    DDRB |= 1<<LED;
}

int TestLed::run_task(char _state) {
    switch (_state) {
        case LED_INIT:
            led_init();
            state = LED_READY;
            break;
        case LED_READY:
            sem_wait(BUTTON_SEM);
            if (event = SIGNAL_EVENT) {
                PORTB ^= 1<<LED;
            }
            break;
        default:
            break;
    }

    return 0;
}