Nave nave;

void Nave::init() {
  pinMode(NAVE_PIN_R, OUTPUT);
  pinMode(NAVE_PIN_G, OUTPUT);
  pinMode(NAVE_PIN_B, OUTPUT);
}

void Nave::prender() {
  digitalWrite(NAVE_PIN_R, LOW);
  digitalWrite(NAVE_PIN_G, LOW);
  digitalWrite(NAVE_PIN_B, LOW);
}

void Nave::apagar() {
  digitalWrite(NAVE_PIN_R, HIGH);
  digitalWrite(NAVE_PIN_G, HIGH);
  digitalWrite(NAVE_PIN_B, HIGH);
}


