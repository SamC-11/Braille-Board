#include <Wire.h>
#include <Servo.h>

//Macros
#define SLAVE_ADDRESS 0x04 //Address of the Arduino in the I2C bus
#define NUMBER_OF_SERVOS 6 //Number of servos in 1 module
#define EXTENDEDR 130 //Degree of servo for a raised bump
#define RETRACTEDR 0 //Degree of servo for an unraised bump
#define NUMBER_OF_SYMBOLS 27 //Allows for modularity and additions. 
#define RETRACTEDL 130
#define EXTENDEDL 0


/** Servo hardware mapping information
 * The motor mapping is as follows, where each square bracket is a servo
 * [1] [4]
 * [2] [5]
 * [3] [6]
 * This as a linear array translates to {1,2,3,4,5,6}
 *
 *Servo numbering information
  *  Follows the hardware mapping information, starts at 1 and ends at 6.
  *  When looping through remember it servo 1 is at index 0
  */

 /** The number passed in is an integer which when converted to binary, turns into 
  */


//Number received from Slave-Pi 
int number = 0;
//bit read from numbers; avoid reinitialization if defined as a global
int currentBit = 0;

//Servos for Module 1
Servo module1Servos[NUMBER_OF_SERVOS];

void setup() {
  Serial.begin(9600); // start serial for output
  Wire.begin(SLAVE_ADDRESS); // initialize i2c as slave
  
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

  module1Servos[0].attach(2);
  module1Servos[1].attach(3);
  module1Servos[2].attach(4);
  module1Servos[3].attach(8);
  module1Servos[4].attach(9);
  module1Servos[5].attach(12);

  for(int i = 0; i < 3; i ++){
    module1Servos[i].write(RETRACTEDL);
    delay(200);
  }

  for(int j = 3; j < 6; j++){
    module1Servos[j].write(RETRACTEDR); 
    delay(200);
  }
  Serial.println("Initialization completed.");
}

void loop(){
  delay(100);
}

// callback function for received data
void receiveData(int byteCount){
  
  while(Wire.available()) { //Reading from Slave-Pi
    number = Wire.read();
 
    for(int i = 0; i < NUMBER_OF_SERVOS; i++){ //setting the state of servos starting with servo 1
      currentBit = bitRead(number, (NUMBER_OF_SERVOS - i) - 1); //checking the value of the corresponding bit
      switch(currentBit){
        case 1:
          if(i < 3){ // if its a servo on the left side
            module1Servos[i].write(EXTENDEDL);
          }else{ //if its a servo on the right side
            module1Servos[i].write(EXTENDEDR);
          }
          
          break;
        case 0:
           if(i < 3){ //if its a servo on the left side
            module1Servos[i].write(RETRACTEDL);
          }else{ // if its a servo on the right side
            module1Servos[i].write(RETRACTEDR);
          }
          break;
      }//switch
    }//for  
  }//while

  //end of function
}

// callback function for sending data
void sendData(){
  Wire.write(number);
}
