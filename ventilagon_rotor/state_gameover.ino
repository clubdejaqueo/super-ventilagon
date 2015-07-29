GameoverState gameover_state;

void GameoverState::setup() {
  audio.play_crash();
  audio.stop_song();
  audio.play_game_over();
  keys_pressed = (boton_cw || boton_ccw);
}

void GameoverState::loop() {
  if (boton_cw == false && boton_ccw == false) {
    keys_pressed = false;
  }
  if (keys_pressed == false && boton_cw && boton_ccw) {
    State::change_state(&resetting_state);
  }
  unsigned long now = micros();
  display.tick(now);
}


