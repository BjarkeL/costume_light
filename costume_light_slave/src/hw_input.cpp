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
            if (PIND & 1<<BUTTON_PIN) {
                sem_signal(BUTTON_SEM);
                wait(25);
            }
            break;
        default:
            break;
    }

    return 0;
}