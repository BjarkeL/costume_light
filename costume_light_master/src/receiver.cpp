#include "receiver.h"

char Receiver::received_val;
char Receiver::new_msg = 0;

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
            if (new_msg && received_val == SYNC) {
                //sem_signal(SYNC_SEM);
                new_msg = 0;
            } else if (new_msg && received_val == RESET) {
                //sem_signal(RESET_SEM);
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