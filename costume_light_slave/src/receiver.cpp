#include "receiver.h"

char Receiver::received_val;
char Receiver::new_msg = 0;

Receiver::Receiver() {

}

void Receiver::receiver_init() {
    Wire.begin(SLAVE_1_ADDRESS);
    TWAR |= SLAVE_1_ADDRESS<<1 | 1;
    Wire.onReceive(receive_event);
}

int Receiver::run_task(char _state) {
    switch (_state) {
        case RECEIVER_INIT:
            receiver_init();
            state = RECEIVER_READY;
            break;
        case RECEIVER_READY:
            if (new_msg) {
                switch (received_val) {
                    case SYNC:
                        sem_signal(SYNC_SEM);
                        sem_signal(GREEN_LED_SEM);
                        break;
                    case RESET:
                        sem_signal(RESET_SEM);
                        break;
                    case ANIMATION_PAUSE:
                        sem_signal(ANIMATION_PAUSE_SEM);
                        sem_signal(YELLOW_LED_SEM);
                        break;
                    case ANIMATION_ON_OFF:
                        sem_signal(ANIMATION_ON_OFF_SEM);
                        sem_signal(RED_LED_SEM);
                        break;
                    case ANIMATION_CYCLE:
                        sem_signal(ANIMATION_CYCLE_SEM);
                    default:
                        break;
                }
                new_msg = 0;
            }
            break;
        default:
            break;
    }

    return 0;
}

void Receiver::receive_event() {
    received_val = Wire.read();
    new_msg = 1;
}