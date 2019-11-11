#include <Wire.h>
#include <Servo.h>

#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;
Servo servo1;

void setup() {
  servo1.attach(3);
  
  Serial.begin(9600); // start serial for output
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
  
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

  servo1.write(180);
  delay(500);
  servo1.write(0);
  Serial.println("Ready!");
}

void loop() {
  delay(100);
}

// callback for received data
void receiveData(int byteCount){

  while(Wire.available()) {
    number = Wire.read();
    Serial.print("data received: ");
    Serial.println(number);

    switch(number){
      case 0:
        //put all servos in position 0 (retracted)
        servo1.write(0);
        delay(500);
        break;
      case 1:
        //generate servos for A
        servo1.write(180);
        delay(500);
        break;
      case 2:
        //generate servos for B
        servo1.detach();
        break;
      case 3:
        //generate servos for C
        break;
      case 4:
        //generate servos for D
        break;
      case 5:
        //generate servos for E
        break;
      case 6:
        //generate servos for F
        break;
      case 7:
        //generate servos for G
        break;
      case 8:
        //generate servos for H
        break;
      case 9:
        //generate servos for I
        break;
      case 10:
        //generate servos for J
        break;
      case 11:
        //generate servos for K
        break;
      case 12:
        //generate servos for L 
        break;
      case 13:
        //generate servos for M
        break;
      case 14:
        //generate servos for N
        break;
      case 15:
        //generate servos for O
        break;
      case 16:
        //generate servos for P
        break;
      case 17:
        //generate servos for Q
        break;
      case 18:
        //generate servos for R
        break;
      case 19:
        //generate servos for S
        break;
      case 20:
        //generate servos for T
        break;
      case 21:
        //generate servos for U
        break;
      case 22:
        //generate servos for V
        break;
      case 23:
        //generate servos for W
        break;
      case 24:
        //generate servos for X
        break;
      case 25:
        //generate servos for Y
        break;
      case 26:
        //generate servos for Z
        break;   
      
    }

  }
}

// callback for sending data
void sendData(){
  Wire.write(number);
}
