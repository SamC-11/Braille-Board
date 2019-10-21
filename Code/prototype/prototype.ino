#include <Servo.h>

Servo servo1;
Servo servo2;
Servo selectedServo;
char moduleOneArray[2] = {'1','1'};

const byte numChars = 32;
char receivedChars[2];

char receivedChar;

boolean newData = false;

void setup() {
  // put your setup code here, to run once:
  servo1.attach(5);
  servo1.write(0);

  servo2.attach(4); 
  servo2.write(0);
  
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int j = 0; j < 10; j++){
    for(int i = 1; i < 3; i++){
      switch(i){
        case 1:
          selectedServo = servo1;
          break;
        case 2:
          selectedServo = servo2;
          break;
        default:
          break;
      }
      switch(moduleOneArray[i-1]){
        case '1':
          selectedServo.write(180);
          delay(500);
          selectedServo.write(0);
          break;
        default:
          break;
      }
  
      
    }
  }
  //delay(500);
  for(int k = 0; k < 30; k++){
    servo1.write(90);
    servo2.write(90);
    delay(100);
    servo1.write(180);
    servo2.write(180);
    delay(100);
  }
  servo1.detach();
  servo2.detach();
}
