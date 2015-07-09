ResettingState resetting_state;

void ResettingState::setup() {
  // nada
}

void ResettingState::loop() {
  // TODO
  // tirar las lineas para afuera durante medio segundo
  // board.step_back();
  unsigned long now = micros();
  display.tick(now);
  
  // TODO
  // despues de medio segundo, arrancar el juego
  State::change_state(&play_state);

}
