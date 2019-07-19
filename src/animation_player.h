#ifndef ANIMATION_PLAYER_H
#define ANIMATION_PLAYER_H

#include "task.h"
#include "FastLED.h"
#include "definitions.h"

#define PLAYER_INIT 0
#define PLAYER_READY 1

class AnimationPlayer: public Task {
public:
    AnimationPlayer();

    void init_player();
    int run_task(char _state);

    void play_frame();
    void reset_animation();
private:
    CRGB leds[NUM_LEDS];
    int frame_index = 0;
    int current_frame = 0;
};

#endif