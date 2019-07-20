#include "animation_player.h"

AnimationPlayer::AnimationPlayer() {

}

void AnimationPlayer::init_player() {
    FastLED.addLeds<WS2812B, LED_STRIP_PIN, GRB>(leds, NUM_LEDS);
    pick_animation(ANIMATION1);
    current_animation = ANIMATION1;
}

int AnimationPlayer::run_task(char _state) {
    switch (_state) {
        case PLAYER_INIT:
            init_player();
            state = PLAYER_READY;
            break;
        case PLAYER_READY:
            if (sem_check(RESET_SEM)) {
                reset_animation(2);
                reset_timer(FRAME_TIMER);
                DDRB ^= 1<<4;
            }
            if (sem_check(SYNC_SEM)) {
                if (current_animation == ANIMATION1) {
                    pick_animation(ANIMATION2);
                    current_animation = ANIMATION2;
                } else {
                    pick_animation(ANIMATION1);
                    current_animation = ANIMATION1;
                }
                DDRB ^= 1<<4;
            }
            if (check_timer(FRAME_TIMER) == TIMER_DONE) {
                play_frame();
                set_timer(0, 50);
            }
            if (sem_check(ANIMATION_PAUSE_SEM)) {
                state = PLAYER_PAUSE;
            }
            if (sem_check(ANIMATION_ON_OFF_SEM)) {
                animation_off();
                state = PLAYER_OFF;
            }
            break;
        case PLAYER_OFF:
            if (sem_check(ANIMATION_ON_OFF_SEM)) {
                state = PLAYER_READY;
            }
            break;
        case PLAYER_PAUSE:
            if (sem_check(ANIMATION_PAUSE_SEM)) {
                state = PLAYER_READY;
            }
            if (sem_check(ANIMATION_ON_OFF_SEM)) {
                animation_off();
                state = PLAYER_OFF;
            }
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
    if (++current_frame == frames) {
        current_frame = 0;
        frame_index = 0;
    }
    FastLED.show();
}

void AnimationPlayer::reset_animation(char _frame) {
    current_frame = _frame;
    frame_index = NUM_LEDS*3*_frame;
}

void AnimationPlayer::pick_animation(char _animation) {
    switch (_animation) {
        case ANIMATION1:
            animation = animation1;
            frames = FRAMES_ANIMATION1;
            break;
        case ANIMATION2:
            animation = animation2;
            frames = FRAMES_ANIMATION2;
            break;
        default:
            break;
    }
    reset_animation(0);
    reset_timer(FRAME_TIMER);
}

void AnimationPlayer::animation_off() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].r = 0;
        leds[i].g = 0;
        leds[i].b = 0;
    }
    FastLED.show();
}