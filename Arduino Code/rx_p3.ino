#include <SoftwareSerial.h>
#include <Servo.h>
#define BTSerial Serial
#define enable 5
#define phase 6
#define FORWARD HIGH
#define BACKWARD LOW
#define BAUDRATE 9600
#define servo_pin 9
Servo servo;
int degree;
int Speed;
// Struct to hold the data we want to receive
struct Packet {
  int x;
  int y;
//  int checksum;
} pkt; // Instantiate a Packet struct
 
void setup() {
  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);
  servo.attach(servo_pin);
  // HM-10 virtual UART
  BTSerial.begin(BAUDRATE);
  pinMode(phase,OUTPUT);
  digitalWrite(phase,FORWARD);
  analogWrite(enable,0);
}
 
void loop() {
  // Receive data from the bluetooth
  bluetooth_receive();
  degree = map(pkt.y,0,1023,50,105);
  Speed = map(pkt.x,0,1023,-255,255);
  if(Speed >=0){
    digitalWrite(phase,FORWARD);
    analogWrite(enable,abs(Speed));
  }
  else{
    digitalWrite(phase,BACKWARD);
    analogWrite(enable,abs(Speed));
  }
  servo.write(degree);
  print_packet();
  delay(50);
}

// Function responsible for receiving data over bluetooth
void bluetooth_receive() {
//  while(BTSerial.available()>0){
//    BTSerial.read
//  }
  // Check the software serial buffer for data to read
  if(BTSerial.available() >= sizeof(Packet)) {
    // Read in the appropriate number of bytes to fit our Packet
    BTSerial.readBytes((byte *) & pkt,sizeof(Packet));
  }  
}

// Function to print packet data (debug)
void print_packet() {  
  Serial.print("RX: (x,y,degree,speed)=(");
  Serial.print(pkt.x); Serial.print(",");
  Serial.print(pkt.y); Serial.print(",");
  Serial.print(degree); Serial.print(",");
  Serial.print(Speed); 
  Serial.println(")");
}
