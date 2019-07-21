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
    DDRD |= 1<<RED_LED;
    DDRD |= 1<<GREEN_LED;
    DDRD |= 1<<YELLOW_LED;
}

int TestLed::run_task(char _state) {
    switch (_state) {
        case LED_INIT:
            led_init();
            state = LED_READY;
            break;
        case LED_READY:
            if (sem_check(RED_LED_SEM))
                PORTD ^= 1<<RED_LED;
            if (sem_check(YELLOW_LED_SEM))
                PORTD ^= 1<<YELLOW_LED;
            if (sem_check(GREEN_LED_SEM)) {
                PORTD |= 1<<GREEN_LED;
                set_timer(LED_FLASH_TIMER, 10);
            }
            if (check_timer(LED_FLASH_TIMER) == TIMER_DONE)
                PORTD &= ~(1<<GREEN_LED);
            break;
        default:
            break;
    }

    return 0;
}