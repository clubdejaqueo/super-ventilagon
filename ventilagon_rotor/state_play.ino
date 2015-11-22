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
  current_level = levels[new_level];
  paused = false;
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
  current_level = levels[section];
}


void PlayState::loop() {
  unsigned long now = micros();

  if (boton_cw != boton_ccw) {
    int new_pos = 0;

    if (boton_cw) {
      new_pos = nave_pos + current_level.rotation_speed;
    }
    if (boton_ccw) {
      new_pos = nave_pos - current_level.rotation_speed;
    }

    new_pos = (new_pos + SUBDEGREES) & SUBDEGREES_MASK;

    boolean colision_futura = board.colision(new_pos, ROW_SHIP);
    if (!colision_futura) {
      nave_pos = new_pos;
    }
  }


  if (now > (last_step + current_level.step_delay)) {
    if (!board.colision(nave_pos, ROW_SHIP)) {
      if (!paused) {
        board.step();
      }
    } else {
      // crash boom bang
      State::change_state(&gameover_state);
    }
    last_step = now;
  }

  display.tick(now);
  display.adjust_drift();

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

