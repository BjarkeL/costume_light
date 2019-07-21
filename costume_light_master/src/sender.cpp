#include "sender.h"

Sender::Sender() {

}

void Sender::sender_init() {
    Wire.begin(MASTER_ADDRESS);
}

int Sender::run_task(char _state) {
    switch (_state) {
        case SENDER_INIT:
            sender_init();
            state = SENDER_READY;
            break;
        case SENDER_READY:
            if (sem_check(SEND_ANIMATION_ON_OFF_SEM)) {
                Wire.beginTransmission(0);
                Wire.write(ANIMATION_ON_OFF);
                Wire.endTransmission();
            }
            if (sem_check(SEND_ANIMATION_PAUSE_SEM)) {
                Wire.beginTransmission(0);
                Wire.write(ANIMATION_PAUSE);
                Wire.endTransmission();
            }
            if (sem_check(SEND_ANIMATION_SYNC_SEM)) {
                Wire.beginTransmission(0);
                Wire.write(SYNC);
                Wire.endTransmission();
            }
            if (sem_check(SEND_ANIMATION_CYCLE_SEM)) {
                Wire.beginTransmission(0);
                Wire.write(ANIMATION_CYCLE);
                Wire.endTransmission();
            }
            /*
            if (++frame_counter == FRAMES_ANIMATION1) {
                frame_counter = 0;
                Wire.beginTransmission(8);
                Wire.write(RESET);
                Wire.endTransmission();
            }
            wait(FRAME_DELAY);
            */
            break;
        default:
            break;
    }

    return 0;
}