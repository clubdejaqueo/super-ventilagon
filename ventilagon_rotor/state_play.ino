PlayState play_state;

void PlayState::setup() {
  board.reset();
  audio.play_song(current_level.song);
  current_section = 0;
}

int PlayState::get_section_for_time(unsigned long now) {
  return 0;
}

void PlayState::check_section(unsigned long now) {
  if (get_section_for_time(now) > current_section) {
    advance_section();
  }
}

void PlayState::advance_section() {
}

void PlayState::loop() {
  unsigned long now = micros();

  if (boton_cw || boton_ccw) {
    int new_pos;

    if (boton_cw) {
      new_pos = nave_pos + 5;
    }
    if (boton_ccw) {
      new_pos = nave_pos - 5;
    }

    new_pos = (new_pos + SUBDEGREES) & SUBDEGREES_MASK;

    boolean colision_futura = board.colision(new_pos, ROW_COLISION);
    if (!colision_futura) {
      nave_pos = new_pos;
    }
  }


  if (now > (last_step + step_delay)) {
    if (!board.colision(nave_pos, ROW_SHIP)) {
      board.step();
    } else {
      // crash boom bang
      State::change_state(&gameover_state);
    }
    last_step = now;
  }

  check_section(now);

  display.tick(now);

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
