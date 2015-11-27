#include <Servo.h>
#include <PlainENCi.h>
#include <Adafruit_NeoPixel.h>
#include <limits.h>

#define CENTISECONDS (10UL) // in milliseconds

unsigned long section_durations[] = {
  1325 * CENTISECONDS,
  1325 * CENTISECONDS,
  1325 * CENTISECONDS,
  1325 * 2 * CENTISECONDS,
  1325 * 3 * CENTISECONDS,
  ULONG_MAX
};

uint32_t colors[] = {
  0x0000ff,
  0x00ff00,
  0xffff00,
  0x00ffff,
  0xff00ff,
  0xff0000,
};

#define NEO_PIN 7
#define LUZ_BOTON_1 2
#define LUZ_BOTON_2 3
#define SERVO 9
#define NUM_PIXELS 16

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_PIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);
Servo myservo;
uint8_t ledPin = PINB5;
int16_t counts;
int16_t _maxCounts = 32767;
int16_t _minCounts = -32767;

uint8_t _ledMask = (1 << PINB5);

int section = 0;
bool timer_running;
unsigned long section_init_time;
unsigned long section_duration = section_durations[section];

void update_servo_colors(uint32_t color) {
  for (int n = 0; n < NUM_PIXELS; n++) {
    pixels.setPixelColor(n, color);
  }
  pixels.show();
}

void update_servo_value(long value, long max_val) {
  // rango = (106,13)
  int s = map(value, 0, max_val, 106, 13);
  myservo.write(s);
}

void apagar_botones() {
  digitalWrite(LUZ_BOTON_1, LOW);
  digitalWrite(LUZ_BOTON_2, LOW);
}

void prender_botones() {
  digitalWrite(LUZ_BOTON_1, HIGH);
  digitalWrite(LUZ_BOTON_2, HIGH);
}

void start_timer() {
  timer_running = true;
  section = 0;
  section_init_time = millis();
  section_duration = section_durations[section];
  update_servo_colors(colors[0]);
  apagar_botones();
}

void stop_timer() {
  timer_running = false;
  prender_botones();
}

void reset_it_all() {
  timer_running = false;
  update_servo_colors(0);
  update_servo_value(0, 255);
  section = 0;
  prender_botones();
}

void advance_section(unsigned long now) {
  section++;
  section_init_time = now;
  section_duration = section_durations[section];
  update_servo_colors(colors[section]);
}

void check_timer() {
  if (timer_running == false) {
    return;
  }
  unsigned long now = millis();
  if (now - section_init_time > section_duration) {
    advance_section(now);
  }
  update_servo_value(now - section_init_time, section_duration);
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();

    switch (inChar) {
      case 's':
        stop_timer();
        break;
      case 'S':
        start_timer();
        break;
      case 'R':
        reset_it_all();
        break;
    }
  }
}

void setup_encoder() {
  ENC.InitializeENC(0, 1, 2, &PORTC, ENC_ONE_DET_PER_PULSE); /* Connects to PORTB, PINB0 (Pin A), PINB1 (Pin B) and PINB2 (Pin C)*/
  //ENC.SetBooster(50, 20); /* If the interval between two pulses is less than 5 ms, apply a multiplication factor which can reach x20 */
  ENC.SetCounter(0, _minCounts, _maxCounts); /* Reset counter */
  counts = ENC.GetCounter(); /* Get counter value */
  Serial.println(counts, DEC); /* Print counter value */
}

void setup() {
  Serial.begin (57600); /* Initialize serial comm port */
  //setup_encoder();
  myservo.attach(SERVO);
  pixels.setBrightness(128);
  pixels.begin();
  pinMode(LUZ_BOTON_1, OUTPUT);
  pinMode(LUZ_BOTON_2, OUTPUT);
  reset_it_all();
}

void check_encoder() {
  static int16_t lastCount = 0;
  if (ENC.PushButtonState() == ENC_BTN_DOWN) { /* Read push button status (Ground true => 0=down) */
    ENC.SetCounter(0, _minCounts, _maxCounts); /* Reset counter */
  }
  counts = ENC.GetCounter(); /* Get counter value */
  if (counts < 0) {
    counts = 0;
  }
  if (counts > 255) {
    counts = 255;
  }
  if (lastCount != counts) { /* If counter has changed since last display */
    Serial.println(counts, DEC); /* Print counter value */
    update_servo_value(counts, 255);

    int c = map(counts, 0, 255, 0, 5);
    uint32_t color = colors[c];
    update_servo_colors(color);
    lastCount = counts; /* Record current counter value */
    /* Toggle control led */
    PORTB ^= _ledMask;
  }
}

void loop() {
  check_timer();
  //check_encoder();
}
