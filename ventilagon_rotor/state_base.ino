State* State::current_state;

void State::change_state (State* new_state) {
#ifdef DEBUG
  Serial.println(new_state->name());
#endif
  State::current_state = new_state;
  State::current_state->setup();
}
