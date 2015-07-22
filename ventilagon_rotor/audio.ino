Audio audio;

void Audio::play_crash() {
  Serial.print("c");
}

void Audio::stop_song() {
  Serial.print("0");
}

void Audio::begin() {
  Serial.print("b");
}

void Audio::play_song(char song) {
  Serial.print(song);
}
