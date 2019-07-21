#ifndef ANIMATION_PLAYER_H
#define ANIMATION_PLAYER_H

#include "task.h"
#include "FastLED.h"
#include "definitions.h"
#include "avr/io.h"

#define PLAYER_INIT 0
#define PLAYER_READY 1
#define PLAYER_PAUSE 2
#define PLAYER_OFF 3

class AnimationPlayer: public Task {
public:
    AnimationPlayer();

    void init_player();
    int run_task(char _state);

    void play_frame();
    void reset_animation(char _frame);
    void pick_animation(char _animation);
    void animation_off();
private:
    CRGB leds[NUM_LEDS];
    int frame_index = 0;
    int current_frame = 0;
    char* animation;
    char current_animation;
    char frames;
    char sync_counter;
};

#endif