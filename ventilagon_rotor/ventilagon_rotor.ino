#include "definitions.h"


int nave_pos = 360;
int nave_calibrate = -478;


volatile unsigned long last_turn = 0;
volatile unsigned long last_turn_duration = 100000L;

void handle_interrupt() {
  unsigned long this_turn = micros();
  last_turn_duration = this_turn - last_turn;
  last_turn = this_turn;
}

unsigned long last_step = 0;


void setup() {
  Serial.begin(57600);

  randomSeed(analogRead(0));
  //randomSeed(83);

  pinMode(HALL_SENSOR, INPUT_PULLUP);
  ledbar.init();
  ship.init();
  board.fill_patterns();
  State::change_state(&play_state);
  attachInterrupt(0, handle_interrupt, FALLING);
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
    }

    if (inChar != 0) {
      if (inChar >= '1' && inChar <= '6') {
        selectLevel(inChar - '1');
      }
      if (inChar == ' ') {
        Serial.print("VELOCIDAD:");
        Serial.println(last_turn_duration);
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
