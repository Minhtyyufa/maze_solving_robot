#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"

class MotorController
{
  public:
    MotorController();
    void turn_left(int velocity);
    void turn_right(int velocity);
    void go_straight(int velocity);
    void brake();
    void go_backwards(int velocity);
};

#endif
