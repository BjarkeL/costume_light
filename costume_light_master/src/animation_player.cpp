#include "animation_player.h"

AnimationPlayer::AnimationPlayer() {

}

void AnimationPlayer::init_player() {
    FastLED.addLeds<WS2812B, LED_STRIP_PIN, GRB>(leds, NUM_LEDS);
    pick_animation(ANIMATION0);
    init_gen_animation();
    current_animation = ANIMATION0;
    sync_counter = (frames*SYNC_INTERVAL)-2;
}

int AnimationPlayer::run_task(char _state) {
    switch (_state) {
        case PLAYER_INIT:
            init_player();
            animation_off();
            state = PLAYER_OFF;
            break;
        case PLAYER_READY:
            if (sem_check(ANIMATION_CYCLE_SEM)) {
                if (current_animation == ANIMATION0) {
                    pick_animation(ANIMATION1);
                    current_animation = ANIMATION1;
                } else if (current_animation == ANIMATION1) {
                    pick_animation(ANIMATION2);
                    current_animation = ANIMATION2;
                } else {
                    pick_animation(ANIMATION0);
                    current_animation = ANIMATION0;
                    init_gen_animation();
                }
                sync_counter = (frames*SYNC_INTERVAL)-2;
            }
            //if (sem_check(RESET_SEM)) {
            //}
            if (check_timer(FRAME_TIMER) == TIMER_DONE) {
                if (current_animation == ANIMATION0) {
                    generated_animation();
                } else {
                    if (++sync_counter == frames*SYNC_INTERVAL) {
                        reset_animation(0);
                        reset_timer(FRAME_TIMER);
                        sem_signal(SEND_ANIMATION_SYNC_SEM);
                        sem_signal(GREEN_LED_SEM);
                        sync_counter = 0;
                    }
                    play_frame();
                }
                set_timer(FRAME_TIMER, FRAME_DELAY);
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
        case ANIMATION0:
            animation = nullptr;
            frames = FRAMES_ANIMATION0;
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

void AnimationPlayer::init_gen_animation() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i].r = random(0,MAX_BRIGHTNESS_RED);
        leds[i].g = random(0,MAX_BRIGHTNESS_GREEN);
        leds[i].b = random(0,MAX_BRIGHTNESS_BLUE);
    }
}

void AnimationPlayer::generated_animation() {
    for (int i = 0; i < NUM_LEDS; i++) {
        int rand_red = random(-5,5);
        int rand_green = random(-5,5);
        int rand_blue = random(-5,5);
        if (leds[i].r + rand_red <= MAX_BRIGHTNESS_RED && leds[i].r >= 0)
            leds[i].r += rand_red;
        if (leds[i].g + rand_green <= MAX_BRIGHTNESS_GREEN && leds[i].g >= 0)
            leds[i].g += rand_green;
        if (leds[i].b + rand_blue <= MAX_BRIGHTNESS_BLUE && leds[i].b >= 0)
            leds[i].b += rand_blue;
    }
    FastLED.show();
}