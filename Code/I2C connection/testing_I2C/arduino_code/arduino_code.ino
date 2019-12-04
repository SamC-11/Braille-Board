#include <Wire.h>
#include <Servo.h>

//Macros
#define SLAVE_ADDRESS 0x04 //Address of the Arduino in the I2C bus
#define NUMBER_OF_SERVOS 6 //Number of servos in 1 module
#define EXTENDED 180 //Degree of servo for a raised bump
#define RETRACTED 0 //Degree of servo for an unraised bump
#define NUMBER_OF_SYMBOLS 27 //Allows for modularity and additions. 

/** Servo hardware mapping information
 * The motor mapping is as follows, where each square bracket is a servo
 * [1] [4]
 * [2] [5]
 * [3] [6]
 * This as a linear array translates to {1,2,3,4,5,6}
 *
 *Servo numbering information
  *  Follows the hardware mapping information, starts at 1 and ends at 6.
  *  When looping through remember it does NOT start at 0.
  */

 /** Index of symbols inside the mapping array initialized below
  *  index 0 = space
  *  index 1 = A
  *  ...
  *  index 26 = Z
  */


//Number received from Slave-Pi 
int number = 0;

//structure made for the servo matrix refer to servo mapping above
typedef struct{
  int first;
  int second;
  int third;
  int fourth;
  int fifth;
  int sixth;
}servoMatrix;


//Servo matrix initializations for supported characters.
//letters
servoMatrix space = {0,0,0,0,0,0}; 
servoMatrix A = {1,0,0,0,0,0}; 
servoMatrix B = {1,1,0,0,0,0}; 
servoMatrix C = {1,0,0,1,0,0}; 
servoMatrix D = {1,0,0,1,1,0};
servoMatrix E = {1,0,0,0,1,0};
servoMatrix F = {1,1,0,1,0,0};
servoMatrix G = {1,1,0,1,1,0};
servoMatrix H = {1,1,0,0,1,0};
servoMatrix I = {0,1,0,1,0,0};
servoMatrix J = {0,1,0,1,1,0};
servoMatrix K = {1,0,1,0,0,0};
servoMatrix L = {1,1,1,0,0,0};
servoMatrix M = {1,0,1,1,0,0};
servoMatrix N = {1,0,1,1,1,0};
servoMatrix O = {1,0,1,0,1,0}; 
servoMatrix P = {1,1,1,1,0,0};
servoMatrix Q = {1,1,1,1,1,0};
servoMatrix R = {1,1,1,0,1,0};
servoMatrix S = {0,1,1,1,0,0};
servoMatrix T = {0,1,1,1,1,0};
servoMatrix U = {1,0,1,0,0,1};
servoMatrix V = {1,1,1,0,0,1};
servoMatrix W = {0,1,0,1,1,1};
servoMatrix X = {1,0,1,1,0,1};
servoMatrix Y = {1,0,1,1,1,1};
servoMatrix Z = {1,0,1,0,1,1};//26 
//symbols coming soon
servoMatrix comma = {0,0,0,0,0,0};
servoMatrix period = {0,0,0,0,0,0};
servoMatrix questionMark = {0,0,0,0,0,0};
servoMatrix exclamationMark = {0,0,0,0,0,0};
servoMatrix colon = {0,0,0,0,0,0};
servoMatrix semiColon = {0,0,0,0,0,0};

//Number mapping for matrix. Slave-Pi will send the index of the braille symbol to display.
servoMatrix *mapping[NUMBER_OF_SYMBOLS] = {&space,&A,&B,&C,&D,&E,&F,&G,&H,&I,&J,&K,&L,&M,&N,&O,&P,&Q,&R,&S,&T,&U,&V,&W,&X,&Y,&Z};

//Servos for Module 1
Servo module1Servos[NUMBER_OF_SERVOS];

void setup() {
  Serial.begin(9600); // start serial for output
  Wire.begin(SLAVE_ADDRESS); // initialize i2c as slave
  
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);

  //initialize servos. Note that Servo mapping beggins at digital PWM pin 1, simply add offset if you want to start at another pin.
  module1Servos[0].attach(1);
  module1Servos[1].attach(2);
  module1Servos[2].attach(3);
  module1Servos[3].attach(4);
  module1Servos[4].attach(8);
  module1Servos[5].attach(10);

  Serial.println("Initialization completed.");
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
    
    servoMatrix current = *(mapping[number]);  //Current servoMatrix now is the same as the servoMatrix in the index sent by Slave-Pi

    for(int i = 0; i < NUMBER_OF_SERVOS; i++){ //Loop through each value in the servo structure
      switch(returnServoValue(&current, i)){ //Select state of servo (extended or retracted), based on value of servo in the matrix
        case 1:
          module1Servos[i].write(EXTENDED); //set servo to EXTENDED state (180 degrees)
          break;
        case 0:
          module1Servos[i].write(RETRACTED); //set servo to RETRACTED state (0 degrees)
          break;
        case -1:
          //exception handling code here
          break;
        default:
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

/**
 * Returns the value of servo in the servoMatrix struct passed in. 
 * This function is used to index the servoMatrix struct.
 */
int returnServoValue(servoMatrix *current, int index){
  int returnValue;
  switch(index){ //Take index input and return value of the servoMatrix structure passed in
    case 1:
      returnValue = current->first;
      break;
    case 2:
      returnValue = current->second;
      break;
    case 3:
      returnValue = current->third;
      break;
    case 4:
      returnValue = current->fourth;
      break;
    case 5:
      returnValue = current->fifth;
      break;
    case 6:
      returnValue = current->sixth;
      break;
    default:
      returnValue = -1; //for exeception handling
      break; 
  }

  return returnValue;
  
}
