#include "sender.h"

Sender::Sender() {

}

void Sender::sender_init() {
    Wire.begin();
}

int Sender::run_task(char _state) {
    switch (_state) {
        case SENDER_INIT:
            sender_init();
            state = SENDER_READY;
            break;
        case SENDER_READY:
            if (++frame_counter == FRAMES_ANIMATION1) {
                frame_counter = 0;
                Wire.beginTransmission(8);
                Wire.write(RESET);
                Wire.endTransmission();
            }
            wait(FRAME_DELAY);
            break;
        default:
            break;
    }

    return 0;
}