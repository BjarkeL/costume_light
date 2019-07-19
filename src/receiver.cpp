#include "receiver.h"

Receiver::Receiver() {

}

void Receiver::receiver_init() {
    Wire.begin(RECEIVER_ID);
    Wire.onReceive(receive_event);
}

int Receiver::run_task(char _state) {
    switch (_state) {
        case RECEIVER_INIT:
            receiver_init();
            state = RECEIVER_READY;
            break;
        case RECEIVER_READY:

            break;
        default:
            break;
    }

    return 0;
}

void Receiver::receive_event() {
    Wire.read();
    PORTB ^= 1<<4;
}