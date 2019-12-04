#include <Wire.h>
#include <Servo.h>

//Macros
#define SLAVE_ADDRESS 0x04 //Address of the Arduino in the I2C bus
#define NUMBER_OF_SERVOS 6 //Number of servos in 1 module
#define EXTENDED 180 //Degree of servo for a raised bump
#define RETRACTED 0 //Degree of servo for an unraised bump
#define NUMBER_OF_SYMBOLS 27 //Allows for modularity and additions. 

Servo servo[6];
int number = 3;
Servo servo1;
int state[6] = {0,0,0,0,0,0};

void setup() {
  Serial.begin(9600); // start serial for output
  Wire.begin(SLAVE_ADDRESS); // initialize i2c as slave
  
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  // put your setup code here, to run once:
  servo[0].attach(8);
  servo[1].attach(10);
  servo[2].attach(3);
  servo[3].attach(4);
  servo[4].attach(5);
  servo[5].attach(7);
  //servo1.attach(2);

}

void loop(){
  delay(100);
}


// callback function for received data
void receiveData(int byteCount){
  
  while(Wire.available()) { //Reading from Slave-Pi
    number = Wire.read();
    Serial.print("data received: ");
    Serial.println(number);   
    
    if(state[number] == 0){
      servo[number].write(EXTENDED);
      delay(500);
      state[number] ^= 1;
    }else{
      servo[number].write(0);
      delay(500);
      state[number] ^= 1;  
    }
    
  }//while
 
}

// callback function for sending data
void sendData(){
  Wire.write(number+1);
}
