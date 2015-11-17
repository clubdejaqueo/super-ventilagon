int nave_pos = 360;
//int nave_calibrate = -478; // ventilador velocidad media
int nave_calibrate = -250; // ventilador velocidad maxima
int half_ship_width = 50;

volatile unsigned long last_turn = 0;
volatile unsigned long last_turn_duration = 10L;

void handle_interrupt() {
  unsigned long this_turn = micros();
  unsigned long this_turn_duration = this_turn - last_turn;
  //if (this_turn_duration < (last_turn_duration >> 2)) {
  //  return;
  //}
  last_turn_duration = this_turn_duration;
  last_turn = this_turn;
}

Display display;

void Display::adjust_drift() {
  int drift_random = random(0, 6000);
  if (drift_random < 7) {
    drift_speed = drift_random - 3;
    if (drift_speed == 0) {
      drift_speed = 4;
    }
  }
}

bool Display::ship_on(int current_pos) {
  if (calibrating) {
    return board.colision(current_pos, ROW_SHIP);
  }

  // NO HAY QUE ARREGLAR NADA ACA

  if (abs(nave_pos - current_pos) < (half_ship_width)) {
    return true;
  }
  if (abs( ((nave_pos + SUBDEGREES / 2) & SUBDEGREES_MASK) -
           ((current_pos + SUBDEGREES / 2) & SUBDEGREES_MASK))
      < (half_ship_width)) {
    return true;
  }
  return false;
}

void Display::tick(unsigned long now) {
  // esto no hace falta calcularlo tan seguido. Una vez por vuelta deberia alcanzar
  drift_pos = (drift_pos + drift_speed) & SUBDEGREES_MASK;

  unsigned long drift = drift_pos * last_turn_duration / SUBDEGREES;
  unsigned int current_pos = ((drift + now - last_turn) * SUBDEGREES / last_turn_duration) & SUBDEGREES_MASK;
  unsigned int current_column = ((drift + now - last_turn) * NUM_COLUMNS / last_turn_duration) % NUM_COLUMNS;

  if (ship_on(current_pos)) {
    ship.prender();
  } else {
    ship.apagar();
  }

  if (current_column != last_column_drawn) {
    board.draw_column(current_column);
  }
}

void Display::calibrate(bool calibrating) {
  this->calibrating = calibrating;
}

void Display::dump_debug() {
  Serial.print("VELOCIDAD:");
  Serial.println(last_turn_duration);
}
