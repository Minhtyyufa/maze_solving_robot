#include "Arduino.h"
#include "MotorController.h"

MotorController::MotorController(){
  //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel B pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel B pin
}

void MotorController::go_straight(int velocity){
  //Motor A forward @ full speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, velocity);   //Spins the motor on Channel A at full speed

  //Motor B forward @ full speed
  digitalWrite(13, HIGH); //Establishes forward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, velocity);   //Spins the motor on Channel B at full speed
}

void MotorController::turn_left(int velocity){
  //Motor A forward @ full speed
  digitalWrite(12, HIGH); //Establishes forward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, velocity);   //Spins the motor on Channel A at full speed

  //Motor B stop
  digitalWrite(8, HIGH);   //Engage the Brake for Channel B
}

void MotorController::turn_right(int velocity){
  //Motor A stop
  digitalWrite(9, HIGH);   //Engage the Brake for Channel A

  //Motor B forward @ full speed
  digitalWrite(13, HIGH); //Establishes forward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, velocity);   //Spins the motor on Channel B at full speed
}

void MotorController::brake(){
  //Motor A stop
  digitalWrite(9, HIGH);   //Engage the Brake for Channel A

  //Motor B stop
  digitalWrite(8, HIGH);   //Engage the Brake for Channel B
}


void MotorController::go_backwards(int velocity){
  //Motor A backward @ full speed
  digitalWrite(12, LOW); //Establishes backward direction of Channel A
  digitalWrite(9, LOW);   //Disengage the Brake for Channel A
  analogWrite(3, velocity);   //Spins the motor on Channel A at full speed

  //Motor B backward @ full speed
  digitalWrite(13, LOW); //Establishes backward direction of Channel B
  digitalWrite(8, LOW);   //Disengage the Brake for Channel B
  analogWrite(11, velocity);   //Spins the motor on Channel B at full speed
}
