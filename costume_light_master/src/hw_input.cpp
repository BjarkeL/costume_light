#include "hw_input.h"

HwInput::HwInput() {

}

void HwInput::hw_init() {
    PORTD |= 1<<ON_BUTTON_PIN;
    PORTD |= 1<<PLAY_BUTTON_PIN;
    PORTD |= 1<<CYCLE_ANIMATION_BUTTON_PIN;
}

int HwInput::run_task(char _state) {
    switch (_state) {
        case HW_INIT:
            hw_init();
            state = HW_READY;
            break;
        case HW_READY:
            if (!(PIND & 1<<ON_BUTTON_PIN)) {
                sem_signal(SEND_ANIMATION_ON_OFF_SEM);
                sem_signal(ANIMATION_ON_OFF_SEM);
                sem_signal(RED_LED_SEM);
                wait(25);
            }
            if (!(PIND & 1<<PLAY_BUTTON_PIN)) {
                sem_signal(SEND_ANIMATION_PAUSE_SEM);
                sem_signal(ANIMATION_PAUSE_SEM);
                sem_signal(YELLOW_LED_SEM);
                wait(25);
            }
            if (!(PIND & 1<<CYCLE_ANIMATION_BUTTON_PIN)) {
                sem_signal(SEND_ANIMATION_CYCLE_SEM);
                sem_signal(ANIMATION_CYCLE_SEM);
                wait(25);
            }
            break;
        default:
            break;
    }

    return 0;
}