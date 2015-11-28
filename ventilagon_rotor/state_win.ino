WinState win_state;

const long win_step_delay = 25;
unsigned long win_last_step = 0;
unsigned long win_started;
const long win_delay_1 = 13250; // 13.25 seconds
const long win_delay_2 = 13250 + win_step_delay * NUM_ROWS * 2; // un poquin mas de 13.25 seconds

void WinState::setup() {
  display.calibrate(true);
  audio.play_win();
  board.win_reset();
  ledbar.set_win_state();
  win_started = millis();
}

void WinState::loop() {
  unsigned long now_ms = millis();
  if ((now_ms - win_last_step) > win_step_delay) {
    win_last_step = now_ms;
    if ((now_ms - win_started) > win_delay_1) {
      board.step_back();
    } else {
      board.win_step_back();
    }
  }

  if ((now_ms - win_started) > win_delay_2) {
    State::change_state(&state_credits);
  }
  unsigned long now = micros();
  display.tick(now);
  display.adjust_drift();
}


