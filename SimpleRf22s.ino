// SimpleRf22s.ino
//
// Author: Edward Ellams
// Copyright (C) 2013 Edward Ellams
// based on code by Mike McCauley copyright (C) 2011 Arduino RF22 library ( http://www.airspayce.com/mikem/arduino/RF22/ )
// License: http://www.gnu.org/licenses/gpl.html GPL version 2
//
// This program allows broadcasting and receiving of simple, unaddressed messages between RF22 modules on the same
//   Arduino board.
//
// This program is designed for use with RF22 compatible transceivers (see http://www.hoperf.com )

// Required includes
// The RF22 library requires the SPI library to be included in the sketch
#include <RF22.h>
#include <SPI.h>

// Define some constants
#define SS_A 10
#define SS_B 9
#define INTERRUPT_A 0
#define INTERRUPT_B 1

// Here we declare the two RF22B chips
// The first parameter is the SS pin (a digital pin)
// The second the interrupt pin (an interrupt pin)
RF22 RF22_A(SS_A, INTERRUPT_A);
RF22 RF22_B(SS_B, INTERRUPT_B);


uint8_t data_A[] = "Hello World!"; // What will be sent from RFM22_A
uint8_t data_B[] = "Why, Hello!"; // What will be sent from RFM22_B

uint8_t buf[RF22_MAX_MESSAGE_LEN]; // The buffer is used in sending messages as a 'storage' variable
uint8_t len = sizeof(buf); // The length of the buffer - used for padding data

// The setup function is called once, and is the first function called upon startup
void setup()
{
  // Begin sending serial data over USB to a computer
  Serial.begin(9600);
  
  // Attempt to initialise the two RFM22B chips
  // Take note if initialisation fails
  if (!RF22_A.init())
    Serial.println("RF22_A init failed");
  if (!RF22_B.init())
    Serial.println("RF22_B init failed");
  
  // Set B to Rx (receive mode)
  RF22_B.setModeRx();
}

// The loop function is the main loop of the program
void loop()
{
  // Send data_A to RF22_B
  Serial.println("Sending from RF22_A to RF22_B");
  RF22_A.send(data_A, sizeof(data_A));
  RF22_A.waitPacketSent(); // Wait for packet to be sent (an interrupt)
  RF22_A.setModeRx(); // Set RF22_A to receive mode
  
  RF22_B.waitAvailable();
  if (RF22_B.recv(buf, &len)) // Wait for RF22_B to receive valid data
  {
    // Output the received data
    Serial.print("RF22_B received: ");
    Serial.println((char*)buf);
  }
  else
  {
    Serial.println("RF22_B didn't receive anything!");
  }
  
  // Send a response from RF22_B to RF22_A (see above)
  Serial.println("Sending from RF22_B to RF22_A");
  RF22_B.send(data_B, sizeof(data_B));
  RF22_B.waitPacketSent();
  RF22_B.setModeRx();
  
  RF22_A.waitAvailable();
  if (RF22_A.recv(buf, &len)) // Wait for RF22_A to receive valid data (see above)
  {
    Serial.print("RF22_A received: ");
    Serial.println((char*)buf);
  }
  else
  {
    Serial.println("RF22_A didn't receive anything!");
  }
  
  // These two lines 'beautify' the serial output
  // A 'cycle' being a run of the loop function
  Serial.println(); // An empty line, so that each 'cycle' can be seen
  delay(1000); // Delay 1 second between 'cycles'
}
