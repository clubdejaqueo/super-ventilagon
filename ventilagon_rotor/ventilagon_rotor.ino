#include "definitions.h"


int nave_pos = 360;

class Nivel {
    const int velocidad;
    const char* cancion;
    const long color;
  public:
    Nivel(int velocidad, char* cancion, long color) : velocidad(velocidad), cancion(cancion), color(color) {
    }
};

Nivel niveles[] = {
  Nivel(1, "A", 0x0000ff),
  Nivel(2, "B", 0x00ff00),
  Nivel(3, "C", 0xff0000),
  Nivel(4, "A", 0x00ffff),
  Nivel(5, "B", 0xff00ff),
  Nivel(6, "C", 0xffff00)
};


const long color_table[] = {
  //  0xff0000,
  //  0xffff00,
  //  0x00ff00,
  //  0xffff00,
  //  0x0000ff,
  //  0x00ff00,
  0x00ffff,
  //  0x808000,
  //  0x404000,
};

class Colorizer {
    volatile byte pos;
    byte plof;
  public:
    long color1;
    long color2;
    Colorizer() {
      plof = 0;
      color1 = color_table[0];
      color2 = 0x000000;
    }
    void step() {
      pos++;
      color1 = color_table[(pos >> 4) % elements_in(color_table)];

      /*
      if ((plof++)==7) {
        plof = 0;
        pos++;
        color1 = color_table[pos%elements_in(color_table)];
      }
      */
    }
};

Colorizer colorizer;

volatile unsigned long last_turn = 0;
volatile unsigned long last_turn_duration = 100000L;

void handle_interrupt() {
  unsigned long this_turn = micros();
  last_turn_duration = this_turn - last_turn;
  last_turn = this_turn;
  colorizer.step();
}

unsigned long last_step = 0;
const unsigned long step_delay = 100000L;


void setup() {
  Serial.begin(57600);

  randomSeed(analogRead(0));
  //randomSeed(83);

  pinMode(HALL_SENSOR, INPUT_PULLUP);
  attachInterrupt(0, handle_interrupt, FALLING);
  ledbar.init();
  nave.init();
  board.fill_patterns();
  State::change_state(&play_state);
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
  }
}

void selectLevel(int level) {
  // TODO
}


void loop() {
  State::current_state->loop();
}
