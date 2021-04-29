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
  sensorThresholds.push_back(200);
  sensorThresholds.push_back(200);
  sensorThresholds.push_back(200);
  sensorArray = new SensorArray(sensors, sensorThresholds);
  
  
}

void loop(){

  //motorController.turn_left(255);
  
  sensorArray->updateSensors();
  sensorArray->printSensorValues();
  //decideWhereToGo();
  //delay(100);

  
}


void decideWhereToGo(){
  if(sensorArray->isJustMiddleOn()){
    motorController.go_straight(255);
  }
}
