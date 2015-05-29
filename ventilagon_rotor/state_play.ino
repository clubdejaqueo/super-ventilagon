PlayState play_state;

void PlayState::setup() {
  board.reset();
}

void PlayState::loop() {
  unsigned long now = micros();

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

  if (boton_cw || boton_ccw) {
    int new_pos;

    if (boton_cw) {
      new_pos = nave_pos + 5;
    }
    if (boton_ccw) {
      new_pos = nave_pos - 5;
    }

    boolean colision_futura = board.colision(new_pos, ROW_COLISION);
    boolean colision_actual = board.colision(nave_pos, ROW_SHIP);

    if (!colision_futura || colision_actual) {
      nave_pos = (new_pos + SUBDEGREES) % SUBDEGREES;
    }
  }


  if (now > (last_step + step_delay)) {
    if (!board.colision(nave_pos, ROW_SHIP)) {
      board.step();
    }
    last_step = now;
  }

  display.step(now);

  /*
  while (1) {
    int wait = micros()-(loop_start+slice);
    if (wait > 16000) {
      delayMicroseconds(10000);
    } else {
      delayMicroseconds(micros()-(loop_start+slice));
      break;
    }
  }
  */

  //colorizer.step();
}


