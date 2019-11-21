#include <Servo.h>

Servo servo1;
char rx_byte;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo1.attach(4);
}

void loop() {
  if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read();       // get the character
  
    // check if a number was received
    if ((rx_byte >= '0') && (rx_byte <= '9')) {
      Serial.print("Number received: ");
      Serial.println(rx_byte);
    }
  } 
}
