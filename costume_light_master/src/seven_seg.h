#ifndef SEVEN_SEG_H
#define SEVEN_SEG_H

#include "task.h"
#include "avr/io.h"

#define DATA_PIN_1 0
#define DATA_PIN_2 1
#define CLOCK_PIN 3
#define MASTER_RESET 2

#define DOT_OFF 0
#define DOT_ON 1

#define SEVEN_SEG_INIT 0
#define SEVEN_SEG_READY 1

class SevenSeg: public Task {
public:
    SevenSeg();

    void seven_seg_init();
    int run_task(char _state);
private:
    void set_display(char _val, bool _dot);

    char numbers[21] = {
        0b11101110,
        0b00101000,
        0b11001101,
        0b01101101,
        0b00101011,
        0b01100111,
        0b11100111,
        0b00101100,
        0b11101111,
        0b00101111,
        0b00010000,
        0b11111110,
        0b00111000,
        0b11011101,
        0b01111101,
        0b00111011,
        0b01110111,
        0b11110111,
        0b00111100,
        0b11111111,
        0b00111111
    };

    int test = 0;
};

#endif