#include <Servo.h> 
#include <PlainENCi.h>
#include <Adafruit_NeoPixel.h>

// rango = 106-13

#define CENTISECONDS (10UL) // in milliseconds

unsigned long section_durations[] = {
  1325 * CENTISECONDS,
  1325 * CENTISECONDS,
  1325 * CENTISECONDS,
  1325 * 2 * CENTISECONDS,
  1325 * 3 * CENTISECONDS,
  ULONG_MAX
};

uint32_t colores[] = {
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

void setup() 
{
	Serial.begin (115200); /* Initialize serial comm port */
	ENC.InitializeENC(0, 1, 2, &PORTC, ENC_ONE_DET_PER_PULSE); /* Connects to PORTB, PINB0 (Pin A), PINB1 (Pin B) and PINB2 (Pin C)*/
	//ENC.SetBooster(50, 20); /* If the interval between two pulses is less than 5 ms, apply a multiplication factor which can reach x20 */
	ENC.SetCounter(0, _minCounts, _maxCounts); /* Reset counter */
	/* Set led pin and blink led */
	BlinkLed(5, 250);
	counts = ENC.GetCounter(); /* Get counter value */
	Serial.println(counts, DEC); /* Print counter value */
        myservo.attach(SERVO);
        pixels.setBrightness(128);
        pixels.begin();        
}

void loop() 
{
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

                int s = map(counts, 0, 255, 106, 13);
                myservo.write(s);
                
                int c = map(counts, 0, 255, 0, 5); 
                uint32_t color = colores[c];
                for (int n=0; n<NUM_PIXELS; n++) {
                  pixels.setPixelColor(n, color);
                }
                pixels.show();
		lastCount = counts; /* Record current counter value */
		/* Toggle control led */
		PORTB ^= _ledMask;
	}
}


/* Set led pin and blink led */
void BlinkLed(uint8_t blinks, uint16_t intervals)
{
	DDRB |= _ledMask;
	PORTB &= ~_ledMask;
	for (uint8_t i = 0; i < (blinks << 1); i++) {
		PORTB ^= _ledMask;	
		delay(intervals >> 1);
	}
}
