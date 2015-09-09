#include <limits.h>

PlayState play_state;

#define SECONDS (1000UL * 1000UL) // in microseconds

unsigned long section_durations[] = {
  10 * SECONDS,
  10 * SECONDS,
  10 * SECONDS,
  15 * SECONDS,
  15 * SECONDS,
  ULONG_MAX
};

char section_sounds[] = {
  '-', 'g', 'o', 'l', 'j', 'f'
};

void PlayState::setup() {
  board.reset();
  audio.begin();
  display.calibrate(false);
  audio.play_song(current_level.song);
  section = 0;
  section_init_time = micros();
  section_duration = section_durations[section];
}

void PlayState::check_section(unsigned long now) {
  if (now - section_init_time > section_duration) {
    advance_section(now);
  }
}

void PlayState::advance_section(unsigned long now) {
  section++;
  section_init_time = now;
  section_duration = section_durations[section];
  audio.play_song(section_sounds[section]);
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

    boolean colision_futura = board.colision(new_pos, ROW_SHIP);
    if (!colision_futura || 1) {
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

  display.tick(now);

  check_section(now);
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

