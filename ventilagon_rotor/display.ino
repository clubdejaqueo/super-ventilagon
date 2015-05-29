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

void Display::step(unsigned long now) {
  drift_pos = (drift_pos + drift_speed) % SUBDEGREES;

  unsigned long pos_width = min(last_turn_duration / SUBDEGREES, 100000L);
  unsigned long column_width = min(last_turn_duration / NUM_COLUMNS, 100000L);

  unsigned long drift = pos_width * drift_pos;
  unsigned int current_pos = ((drift + now - last_turn) / pos_width) % SUBDEGREES;
  unsigned int current_column = ((drift + now - last_turn) / column_width) % NUM_COLUMNS;

  // FIXME: arreglar cuando la nave cruza la zona oscura,
  //        que se va a ver finito
  if (abs(nave_pos - current_pos) < NAVE_WIDTH / 2) {
    ship.prender();
  } else {
    ship.apagar();
  }

  if (current_column != last_column_drawn) {
    board.draw_column(current_column, ledbar);
    ledbar.update();
  }
}

