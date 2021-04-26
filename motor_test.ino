#include "MotorController.h"
MotorController motorController;
void setup() {
  
  

  Serial.begin(9600);
}

void loop(){

  //motorController.turn_left(255);
  
  // read the input on analog pin 0:
  int sensorValue = (A1);

  Serial.println(sensorValue);

  
}
