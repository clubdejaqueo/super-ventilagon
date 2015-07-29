#include <Servo.h> 
 
Servo myservo;

//int resistencias[] = {0, 203, 409, 615, 819, 1023};

void setup() 
{ 
  Serial.begin(57600);
  myservo.attach(9);
} 
 
void loop() 
{ 
  int v = analogRead(A0);    
  
  int k;
  if (v < 100) {
    k = 5;
  } else if (v < 300) {
    k = 4;
  } else if (v < 500) {
    k = 3;
  } else if (v < 700) {
    k = 2;
  } else if (v < 900) {
    k = 1;
  } else {
    k = 0;
  }
  
  int s = map(k, 0, 5, 30, 120);
  myservo.write(s);

  Serial.println(k);
  delay(50);
}
