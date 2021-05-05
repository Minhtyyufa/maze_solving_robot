#ifndef SensorArray_h
#define SensorArray_h

#include "Arduino.h"
#include <Vector.h>

class SensorArray
{
  private:
    //from left to right, ascending order
    Vector<int> sensors;
    
    //Sensor Values
    Vector<bool> sensorValues;

    //Sensor Thresholds
    Vector<int> sensorThresholds;
    
  public:
    

    
    SensorArray(Vector<int> sensors, Vector<int> sensorThresholds);
    bool isLeftMostOn();
    bool isRightMostOn();
    bool isLeftOn();
    bool isRightOn();
    bool isJustMiddleOn();
    bool areAllOn();
    bool areAllOff();
    void getMiddles(bool values[]);
    
    void updateSensors();
  
    void printSensorValues();
};

#endif
