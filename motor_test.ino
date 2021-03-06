#include "MotorController.h"
#include <Vector.h>
#include "SensorArray.h"
MotorController motorController;

SensorArray* sensorArray = NULL;
unsigned long time_since_not_left = millis();
bool wasOn = false;
unsigned long currentTime;
bool finished = false;
bool wasStraight = false;

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
  sensorThresholds.push_back(250);
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

void goLeftUntilResetPoint(){
  //bool resetPointHit = false;
  bool leftMostTurnedOff = false;
  bool middles[3];
  while(1){
    if(!sensorArray->isLeftMostOn()){
      leftMostTurnedOff = true;  
    }
    if(leftMostTurnedOff){
      sensorArray->getMiddles(middles);
      if(middles[0] && middles[1] && middles[2]){
        break;
      }
    }   
  }
}

void decideWhereToGo(){
  bool middles[3];
  sensorArray->getMiddles(middles);
  bool ignoreLeft = millis() - time_since_not_left > 1000;
  
  if (sensorArray->areAllOn()){
    Serial.println("ALL ON");
    if (!wasOn){
      currentTime = millis();
      wasOn = true;
    }
    else if (millis() - currentTime >= 500 ){
      motorController.brake();
      Serial.println("STOPPED");
      finished = true;
    }
  }
  else{
    wasOn = false; 
  }

  if (!finished){
    
    if (!ignoreLeft && middles[0] && !middles[2]){
      Serial.println("turn left");
      motorController.turn_left(128);
    } else if(!ignoreLeft && sensorArray->isLeftMostOn()){
      wasStraight = false;
      motorController.turn_left(128);
      delay(1500);
    } else if(!ignoreLeft && middles[0] && middles[2]){
      Serial.println("I go straight");
      motorController.go_straight(64);
      wasStraight = true;
    } else if (!middles[0] && middles[2]){
      wasStraight = false;
      
  //        Serial.println("turn right");
      time_since_not_left = millis();
      motorController.turn_right(128);  
      if(ignoreLeft)
        delay(500);
    }else if (sensorArray->isRightMostOn()) {
      wasStraight = false;
      time_since_not_left = millis();
      motorController.turn_right(128);
      if(ignoreLeft)
        delay(500);
      
    } else if(wasStraight && sensorArray->areAllOff()){
        motorController.turn_left(128);
    } 
    else {
      //motorController.brake();
    }
  }

}
