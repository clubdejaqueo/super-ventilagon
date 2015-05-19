boolean last_tecla_izq = false;
boolean last_tecla_der = false;

const byte PIN_IZQ = 2;
const byte PIN_DER = 3;

void setup() {
    Serial.begin(57600);
    pinMode(PIN_IZQ, INPUT_PULLUP);
    pinMode(PIN_DER, INPUT_PULLUP);
}

void loop() {
  boolean tecla_izq = !digitalRead(PIN_IZQ);
  boolean tecla_der = !digitalRead(PIN_DER);
  
  if (tecla_izq != last_tecla_izq) {
    if (tecla_izq) {
      Serial.write("L");
    } else {
      Serial.write("l");
    }
    last_tecla_izq = tecla_izq;
  }
  if (tecla_der != last_tecla_der) {
    if (tecla_der) {
      Serial.write("R");
    } else {
      Serial.write("r");
    }
    last_tecla_der = tecla_der;
  }
}

