#include "seven_seg.h"

SevenSeg::SevenSeg() {

}

void SevenSeg::seven_seg_init() {
    DDRC |= 1<<DATA_PIN_1;
    DDRC |= 1<<DATA_PIN_2;
    DDRC |= 1<<CLOCK_PIN;
    DDRC |= 1<<MASTER_RESET;
    PORTC |= 1<<DATA_PIN_2;
    PORTC &= ~(1<<MASTER_RESET);
    PORTC &= ~(1<<CLOCK_PIN);
}

int SevenSeg::run_task(char _state) {
    switch (_state) {
        case SEVEN_SEG_INIT:
            seven_seg_init();
            state = SEVEN_SEG_READY;
            break;
        case SEVEN_SEG_READY:
            set_display(test, DOT_OFF);
            if (test++ == 20) {
                test = 0;
            }
            wait(50);
            break;
        default:
            break;
    }
}

void SevenSeg::set_display(char _val, bool _dot) {
    char value;
    if (!_dot)
        value = numbers[_val];
    else
        value = numbers[_val+11];
    
    char mask = 0b00000001;
    for (char i = 0; i < 8; i++) {
        // Set the value
        if (value&mask)
            PORTC |= 1<<DATA_PIN_1;
        else
            PORTC &= ~(1<<DATA_PIN_1);
        mask = mask<<1;
        PORTC |= 1<<CLOCK_PIN;
        PORTC &= ~(1<<CLOCK_PIN);
    }
}