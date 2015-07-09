Audio audio;

void Audio::play_crash() {
  Serial.print("c0");
}

void Audio::play_song(char song) {
  Serial.print(song);
}
