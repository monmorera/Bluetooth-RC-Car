// Custom one-way communication with Bluetooth HM-10
// Transmitting data in the form of a struct to receiver
//
// Writes (hardcoded) data to the software UART 
//  and prints the transmitted packet


// Library to make a Software UART
#include <SoftwareSerial.h>

#define TX 1
#define RX 2
#define thumbstick_x A2
#define thumbstick_y A3
SoftwareSerial BTSerial(RX, TX); // (RX, TX)

#define BAUDRATE 9600

// Struct to hold the data we want to transmit
struct Packet {
  int raw_analog_reading_y;
  int raw_analog_reading_x;
} pkt; // Instantiate a Packet struct
 
void setup() {
  // Start Serial Monitor for feedback
  Serial.begin(BAUDRATE);

  // HM-10 virtual UART
  BTSerial.begin(BAUDRATE);  
}
 
void loop() {  
  // Transmit data via bluetooth
  bluetooth_transmit();  

  // Necessary forced delay, if we transmit too fast (no delay)
  //  the error rate increases
  delay(10);
}

// Function responsible for transmitting data over bluetooth
void bluetooth_transmit() {
  // Update data to be transmitted
  pkt.raw_analog_reading_y = analogRead(thumbstick_y);
  pkt.raw_analog_reading_x = analogRead(thumbstick_x);
  
  // Write packet data to the bluetooth - and transmit
  BTSerial.write((byte *) & pkt,sizeof(Packet));

  // Print packet (debug)
//  print_packet();
}
