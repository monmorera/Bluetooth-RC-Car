// Custom one-way communication with Bluetooth HM-10
// Receiving data in the form of a struct from transmitter
//
// Reads from the software UART and prints the received packet


// Library to make a Software UART
#include <SoftwareSerial.h>
#include <Servo.h>
#define enable 5
#define phase 6
#define FORWARD HIGH
#define BACKWARD LOW
#define BAUDRATE 9600
#define servo_pin 0
#define RX 3
#define TX 2
int reading_y;
int reading_x;
int degree;
int Speed;
#define BAUDRATE 9600
#define BTSerial Serial
Servo servo;

// Struct to hold the data we want to receive
struct Packet {
  int Y;
  int X;
} pkt; // Instantiate a Packet struct
 
void setup() {
  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);

  // HM-10 virtual UART
  BTSerial.begin(BAUDRATE);
  servo.attach(servo_pin);
  // Set phase (digital) pin as an output
  pinMode(phase,OUTPUT);

  // Set initial condition for motor driver
//  digitalWrite(phase,FORWARD);
//  analogWrite(enable,0);
}

void loop() {{
  // Receive data from the bluetooth
  bluetooth_receive();
  reading_y = pkt.Y;
  reading_x = pkt.X;
  degree = map(reading_x,0,1023,50,105);
  servo.write(degree);

  }
  delay(10);
}

// Function responsible for receiving data over bluetooth
void bluetooth_receive() {
  // Check the software serial buffer for data to read
  if(BTSerial.available() >= sizeof(Packet)) {
    // Read in the appropriate number of bytes to fit our Packet
    BTSerial.readBytes((byte *) & pkt,sizeof(Packet));
    // Print packet (debug)
    print_packet();
  }   
}

// Function to print packet data (debug)
void print_packet() {  
  Serial.print("RX: (X,Y)=(");
  Serial.print(pkt.X); Serial.print(",");
  Serial.print(pkt.Y); Serial.print(",");
  Serial.println(")");
}
