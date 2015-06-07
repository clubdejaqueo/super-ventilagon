GameoverState gameover_state;

void GameoverState::setup() {

}

void GameoverState::loop() {
  unsigned long now = micros();
  display.tick(now);
}


