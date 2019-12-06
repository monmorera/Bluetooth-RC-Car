// Custom one-way communication with Bluetooth HM-10
// Transmitting data in the form of a struct to receiver
//
// Writes (hardcoded) data to the software UART 
//  and prints the transmitted packet


// Library to make a Software UART
#include <SoftwareSerial.h>
#define thumbstick_x A2
#define thumbstick_y A3
#define TX 1
#define RX 2
int y;
int x;
//int checksum;
SoftwareSerial BTSerial(RX, TX); // (RX, TX)

#define BAUDRATE 9600

// Struct to hold the data we want to transmit
struct Packet {
  int x;
  int y;
//  int checksum;
};
Packet pkt; // Instantiate a Packet struct
 
void setup() {
  // HM-10 virtual UART
  BTSerial.begin(BAUDRATE);  
}
 
void loop() {  
  // Transmit data via bluetooth
  pkt.y = analogRead(thumbstick_y);
  pkt.x = analogRead(thumbstick_x);
//  pkt.checksum = pkt.x^pkt.y;
  BTSerial.write((byte *) & pkt,sizeof(Packet));
  // Necessary forced delay, if we transmit too fast (no delay)
  //  the error rate increases
  delay(50);
}
