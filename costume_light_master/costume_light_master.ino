#include "src/definitions.h"
#include "src/task.h"
#include "src/animation_player.h"
#include "src/hw_input.h"
#include "src/leds.h"
#include "src/receiver.h"
#include "src/sender.h"


char current_task = 0;
Task** tasks = new Task*[MAX_TASKS];

void add_task(Task* _t, char _id);

void setup() {
  for (char i = 0; i < MAX_TASKS; i++) {
    tasks[i] = new Task;
    tasks[i]->condition = TASK_IDLE;
  }
  add_task(new AnimationPlayer, ANIMATION_TASK);
  add_task(new HwInput, BUTTON_TASK);
  add_task(new StatusLed, STATUS_LED_TASK);
  add_task(new TestLed, TEST_LED_TASK);
  add_task(new Receiver, RECEIVER_TASK);
  //add_task(new Sender, SENDER_TASK);
}

void loop() {

  timing = millis();

  while (tasks[current_task]->condition != TASK_IDLE) {
    tasks[current_task++]->update_task();
  }
  Task::update_timers();
  current_task = 0;

  while (millis() - timing < FREQUENZY);
}

void add_task(Task* _t, char _id) {
  tasks[_id] = _t;
  tasks[_id]->set_id(_id);
  tasks[_id]->condition = TASK_READY;
  tasks[_id]->state = 0;
  tasks[_id]->event = 0;
  tasks[_id]->sem = 0;
  tasks[_id]->timer = 0;
}
