#include "animation_player.h"

AnimationPlayer::AnimationPlayer() {

}

void AnimationPlayer::init_player() {
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

int AnimationPlayer::run_task(char _state) {
    switch (_state) {
        case PLAYER_INIT:
            init_player();
            state = PLAYER_READY;
            break;
        case PLAYER_READY:
            play_frame();
            wait(FRAME_DELAY);
            break;
        default:
            break;
    }

    return 0;
}

void AnimationPlayer::play_frame() {
    int index = 0;
    for (int i = 0; i < NUM_LEDS*3; i+=3) {
        leds[index].b = pgm_read_byte_near(animation+frame_index+i);
        leds[index].g = pgm_read_byte_near(animation+frame_index+i+1);
        leds[index++].r = pgm_read_byte_near(animation+frame_index+i+2);
    }
    frame_index += NUM_LEDS*3;
    if (++current_frame == FRAMES) {
        current_frame = 0;
        frame_index = 0;
    }
    FastLED.show();
}

void AnimationPlayer::reset_animation() {
    current_frame = 0;
    frame_index = 0;
}