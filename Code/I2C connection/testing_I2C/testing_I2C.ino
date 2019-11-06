#include <Wire.h>
#include <Servo.h>

#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;
Servo servo1;

void setup() {
  servo1.attach(4);
  
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
    
    if (number == 1){  
      servo1.write(180);
      delay(500);
    }

    if(number == 0){
      servo1.write(0);
      delay(500);
    }

    if(number == 2){
      servo1.detach();
    }
  }
}

// callback for sending data
void sendData(){
  Wire.write(number);
}
