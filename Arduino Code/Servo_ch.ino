#include <Servo.h>
#define thumbstick_x A0
#define thumbstick_y A1
#define enable 5
#define phase 6
#define FORWARD HIGH
#define BACKWARD LOW
#define BAUDRATE 9600
#define servo_pin 9
int degree;
int Speed;
int raw_analog_reading_y;
int raw_analog_reading_x;
Servo servo;
void setup() {

  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);
  // Attach servo pin to Servo object  
  servo.attach(servo_pin);
  // Set phase (digital) pin as an output
  pinMode(phase,OUTPUT);

  // Set initial condition for motor driver
  digitalWrite(phase,FORWARD);
  analogWrite(enable,0);
}
void loop() { 
  raw_analog_reading_y = analogRead(thumbstick_y);
  raw_analog_reading_x = analogRead(thumbstick_x);
  degree = raw_analog_reading_x*18/67;
  Speed =  raw_analog_reading_y*25/67;
  Serial.print("X =  ");
  Serial.print(raw_analog_reading_x);
  Serial.print("  ");
  Serial.print("degree = ");
  Serial.print(degree);
  Serial.print("  ");
  servo.write(degree);
  if(raw_analog_reading_y >= 337){
        digitalWrite(phase,FORWARD);
        Speed = (raw_analog_reading_y - 337) * 25/3 8;
        analogWrite(enable,Speed);
        Serial.print("Y =  ");
        Serial.print(raw_analog_reading_y);
        Serial.print("  ");
        Serial.print("Speed = ");
        Serial.print(Speed);
        Serial.print("  ");
        Serial.print("FORWARD");
        Serial.print("  ");
        Serial.println(); 
  }
  else{
        digitalWrite(phase,BACKWARD);
        Speed = abs(raw_analog_reading_y-337) * 25/38;
        analogWrite(enable,Speed);
        Serial.print("Y =  ");
        Serial.print(raw_analog_reading_y);
        Serial.print("  ");
        Serial.print("Speed = ");
        Serial.print(Speed);
        Serial.print("  ");
        Serial.print("BACKWARD");
        Serial.print("  ");
        Serial.println(); 
  }
//  analogWrite(enable,Speed); 
  delay(50);
}
