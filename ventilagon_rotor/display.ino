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
  if (abs(nave_pos - current_pos) < (SHIP_WIDTH / 2)) {
    return true;
  }
  if (abs( ((nave_pos + SUBDEGREES / 2) & SUBDEGREES_MASK) - 
           ((current_pos + SUBDEGREES / 2) & SUBDEGREES_MASK))
         < (SHIP_WIDTH / 2)) {
    return true;
  }
  return false;
}

void Display::tick(unsigned long now) {
  drift_pos = (drift_pos + drift_speed) & SUBDEGREES_MASK;

  unsigned long pos_width = min(last_turn_duration / SUBDEGREES, 100000L);
  unsigned long column_width = min(last_turn_duration / NUM_COLUMNS, 100000L);

  unsigned long drift = pos_width * drift_pos;
  unsigned int current_pos = ((drift + now - last_turn) / pos_width) & SUBDEGREES_MASK;
  unsigned int current_column = ((drift + now - last_turn) / column_width) % NUM_COLUMNS;

  if (ship_on(current_pos)) {
    ship.prender();
  } else {
    ship.apagar();
  }

  if (current_column != last_column_drawn) {
    board.draw_column(current_column, ledbar);
    ledbar.update();
  }
}

