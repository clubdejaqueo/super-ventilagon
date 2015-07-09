#include "definitions.h"


int nave_pos = 360;


volatile unsigned long last_turn = 0;
volatile unsigned long last_turn_duration = 100000L;

void handle_interrupt() {
  unsigned long this_turn = micros();
  last_turn_duration = this_turn - last_turn;
  last_turn = this_turn;
  debugln("int");
}

unsigned long last_step = 0;
const unsigned long step_delay = 100000L;


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
    }

    if (inChar != 0) {
      if (inChar >= '1' && inChar <= '6') {
        selectLevel(inChar - '1');
      }
      if (inChar == ' ') {
        Serial.print("velocidad:");
        Serial.println(last_turn_duration);
      }
      if (inChar == 'n') {
        board.fill_patterns();
      }
      inChar = 0;
    }    
  }
}

void selectLevel(int level) {
  Level& current_level = levels[0];
  State::change_state(&resetting_state);
}

void loop() {
  State::current_state->loop();
}
