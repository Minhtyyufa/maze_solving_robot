#include "MotorController.h"
#include <Vector.h>
#include "SensorArray.h"
MotorController motorController;

SensorArray* sensorArray = NULL;
void setup() {
  Serial.begin(9600);

  int storage_array[5];
  int storage_array1[5];
  
  Vector<int> sensors;
  sensors.setStorage(storage_array);
  
  sensors.push_back(A1);
  sensors.push_back(A2);
  sensors.push_back(A3);
  sensors.push_back(A4);
  sensors.push_back(A5);

  
  Vector<int> sensorThresholds;
  sensorThresholds.setStorage(storage_array1);
  sensorThresholds.push_back(200);
  sensorThresholds.push_back(200);
  sensorThresholds.push_back(300);
  sensorThresholds.push_back(200);
  sensorThresholds.push_back(250);
  sensorArray = new SensorArray(sensors, sensorThresholds);
  
  
}

void loop(){

  //motorController.turn_left(255);
  
  sensorArray->updateSensors();
  sensorArray->printSensorValues();
  decideWhereToGo();


  
}


void decideWhereToGo(){
  bool middles[3];
  sensorArray->getMiddles(middles);
  if(sensorArray->isLeftMostOn()){
 
    motorController.turn_left(128);
  } else if(middles[0] && middles[2]){
    Serial.println("I go straight");
    motorController.go_straight(128);
  }  else if (middles[0] && !middles[2]){
    Serial.println("turn left");
    motorController.turn_left(128);
  } else if (!middles[0] && middles[2]){
//        Serial.println("turn right");
    motorController.turn_right(128);  
  }else if (sensorArray->isRightMostOn()) {
    motorController.turn_right(128);
  } else {
    //motorController.brake();
  }
}
