#include "definitions.h"

unsigned long last_step = 0;

void setup() {
  pinMode(HALL_SENSOR, INPUT_PULLUP);
  attachInterrupt(0, handle_interrupt, FALLING);
  Serial.begin(57600);

  randomSeed(analogRead(0));
  //randomSeed(83);

  ledbar.init();
  ship.init();
  board.fill_patterns();
  new_level = 0;

  ledbar.reset();
  audio.stop_song();
  audio.play_superventilagon();
  State::change_state(&resetting_state);
}

bool boton_cw = false;
bool boton_ccw = false;

char inChar = 0;

void serialEvent() {
  while (Serial.available()) {
    inChar = (char)Serial.read();

    switch (inChar) {
      case 'L':
        boton_ccw = true;
        break;
      case 'l':
        boton_ccw = false;
        break;
      case 'R':
        boton_cw = true;
        break;
      case 'r':
        boton_cw = false;
        break;
      case ' ':
        play_state.toggle_pause();
        break;
      case '-':
        finetune_minus();
        break;
      case '=':
        finetune_plus();
        break;
      case 'x':
        finetune_next();
        break;
    }

    if (inChar != 0) {
      if (inChar >= '1' && inChar <= '6') {
        selectLevel(inChar - '1');
      }
      if (inChar == ' ') {
        display.dump_debug();
      }
      if (inChar == 'n') {
        board.fill_patterns();
      }
      inChar = 0;
    }
  }
}

void selectLevel(byte level) {
  new_level = level;
  audio.play_crash();
  State::change_state(&resetting_state);
}

void loop() {
  State::current_state->loop();
}
