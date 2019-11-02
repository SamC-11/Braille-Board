#include <Servo.h>
#include <SPI.h>


Servo servo[2];
char moduleOneArray[3] = {'0', '0', '0'};

const byte numChars = 32;
char receivedChars[2];

char receivedChar;

boolean newData = false;

void setup() {
  // put your setup code here, to run once:
  configureServos();
  Serial.begin(9600);
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
//  for(int i = 1; i < 3; i++){
//    switch(i){
//      case 1:
//        selectedServo = servo1;
//        break;
//      case 2:
//        selectedServo = servo2;
//        break;
//      default:
//        break;
//    }//switch
//    switch(moduleOneArray[i-1]){
//      case '1':
//        selectedServo.write(180);
//        delay(500);
//        selectedServo.write(0);
//        break;
//      default:
//        break;
//    }//switch
//  }//for i

  



//  servo1.detach();
//  servo2.detach();
}

void configureServos(){
  for(int i = 4; i < 6; i++){
    servo[i].attach(i);
    servo[i].write(0);
  }
}
