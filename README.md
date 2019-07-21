# Realtime system for running LED strips with Arduino.
Uses a "run to complete" scheduler for multitasking.
The main loop runs through every 10 ms.
The master arduino communicates to all slaves via I2C using the [Wire](https://www.arduino.cc/en/reference/wire) library (broadcast on address 0 enabled).
The LED strips are controlled using the [FastLED](https://github.com/FastLED/FastLED) library.

## Values to adjust across all devices:
*definitions.h:*
* Animations
* Frame numbers
* Number of LED's
* Frame delay
*animation_player.cpp*
* Initial animation *init_player()*

## Values to adjust for the master:
*definitions.h*
* Sync interval

## Values to adjust across all slaves:
*receiver.cpp*
* Slave address *receiver_init()*

## Adding an animation:
*definitions.h*
* Add a define for the animation.
* Add a define for the number of frames.
* Add the animation as a list of rgb values.
*animation_player.cpp*
* Add the animation to the *pick_animation()* function.
* Add the animation to the choice of animations (to be implemented).

## Pins (Arduino Nano):
* Status LED: D13 *PB5 - Built-in LED*
* Green LED: D2 *PD2*
* Yellow LED: D3 *PD3*
* Red LED: D4 *PD4*
* Button 1: D5 *PD5*
* Button 2: D6 *PD6*
* Button 3: D7 *PD7*
* LED strip: D8
* SDA: A4
* SCL: A5

### Button functions:
* Button 1: Pause/play the animation. Also works while the animation is off.
* Button 2: Turn the lights on/off.
* Button 3: Cycles through animations. *Functionality to be updated*.

### LED signals:
* Status LED: Blinks once every second when the program is running.
* Green LED: Flashes for 100 ms every time a sync signal is sent.
* Yellow LED: Lights up while the animation is paused.
* Red LED: Lights up while the LED strips are turned on.

## To-do:
- [ ] Add binary codes for different animations.
- [ ] Add a reset button or delete definitions for manual reset.

### Notes:
All tasks have to be in increasing order without gaps. To avoid this; change the *while (tasks[current_task]->condition != TASK_IDLE)*, to a for loop that skips any gaps.

The receiver only reads one byte so don't send more than one byte.

Seems like it doesn't like if two messages are sent out in one cycle.
