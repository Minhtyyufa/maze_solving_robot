#include "Arduino.h"
#include "SensorArray.h"
#include <Vector.h>


SensorArray::SensorArray(Vector<int> sensors, Vector<int> sensorThresholds){
  this->sensors = sensors;
  this->sensorThresholds = sensorThresholds;
  bool storage[5];
  this->sensorValues.setStorage(storage);
  for(int i = 0; i < this->sensors.size(); i++){
    this->sensorValues.push_back(false);
  }
}

void SensorArray::updateSensors(){
  for(int i = 0; i < this->sensors.size(); i++){
    int reading = analogRead(this->sensors[i]);
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print("value: ");
    Serial.println(reading);
    if(reading >= this->sensorThresholds[i]){
      this->sensorValues[i] = false;
    } else {
      this->sensorValues[i] = true;
    }
  }
}


bool SensorArray::isLeftMostOn(){
  return this->sensorValues[0];
}

bool SensorArray::isRightMostOn(){
  return this->sensorValues[this->sensorValues.size() - 1];
}

bool SensorArray::isJustMiddleOn() {
  for(int i = 0; i < this->sensorValues.size(); i++){
    if(i == this->sensorValues.size()/2){
      if(!this->sensorValues[i]){
        return false; 
      } 
    } else {
      if(this->sensorValues[i]){
        return false;
      }
    }
  }
  return true;
}

//bool SensorArray::isJustMiddleOn() {
//  for(int i = 0; i < this->sensorValues.size(); i++){
//    if(i == this->sensorValues.size()/2){
//      if(!this->sensorValues[i]){
//        return false; 
//      } 
//    } else {
//      if(this->sensorValues[i]){
//        return false;
//      }
//    }
//  }
//  return true;
//}

// returns values of the three middle sensors
void SensorArray::getMiddles(bool values[]) {
  int middleSensor = this->sensorValues.size()/2;
  values[0] = this->sensorValues[middleSensor-1];
  values[1] = this->sensorValues[middleSensor];
  values[2] = this->sensorValues[middleSensor+1];
  return values;
}

bool SensorArray::isLeftOn(){
  for(int i = 0; i < this->sensorValues.size()/2; i++){
    if(this->sensorValues[i]){
      return true;
    }
  }

  return false;
}

bool SensorArray::isRightOn(){
  for(int i = this->sensorValues.size()/2+1; i < this->sensorValues.size(); i++){
    if(this->sensorValues[i]){
      return true;
    }
  }

  return false;
}

void SensorArray::printSensorValues(){
  Serial.println("Printing Sensor Values...");
  Serial.println(this->sensors.size());
  for(int i = 0; i < this->sensorValues.size(); i++){
    Serial.print("Sensor ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(this->sensorValues[i]); 
  }
}
