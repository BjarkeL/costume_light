#include "hw_input.h"

HwInput::HwInput() {

}

void HwInput::hw_init() {

}

int HwInput::run_task(char _state) {
    switch (_state) {
        case HW_INIT:
            hw_init();
            state = HW_READY;
            break;
        case HW_READY:
            if (PINH & 1<<ON_BUTTON_PIN) {
                sem_signal(SEND_ANIMATION_ON_OFF_SEM);
                sem_signal(ANIMATION_ON_OFF_SEM);
                sem_signal(BUTTON_SEM);
                wait(25);
            }
            if (PINH & 1<<PLAY_BUTTON_PIN) {
                sem_signal(SEND_ANIMATION_PAUSE_SEM);
                sem_signal(ANIMATION_PAUSE_SEM);
                sem_signal(BUTTON_SEM);
                wait(25);
            }
            break;
        default:
            break;
    }

    return 0;
}