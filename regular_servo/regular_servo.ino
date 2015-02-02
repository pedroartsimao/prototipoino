#include <Servo.h> 

#define SERVO_PIN             3  // Pino do servo
Servo myservo;

void setup() { 
  myservo.attach(SERVO_PIN);  // Atribui o pino do servo ao objeto 
  myservo.write(90); 
} 
 
void loop() { 
} 
