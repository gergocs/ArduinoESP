#include <Arduino.h>

#include "joystick.h"

Joystick::Joystick(void){
  this->vrXPin = 0;
  this->vrYPin = 0;
  this->swPin = 0;
}
Joystick::Joystick(int vrXPin, int vrYPin, int swPin){
  this->vrXPin = vrXPin;
  this->vrYPin = vrYPin;
  this->swPin = swPin;
  pinMode(this->swPin, INPUT);
  digitalWrite(this->swPin, HIGH);
}
int Joystick::getX(void){
  return analogRead(this->vrXPin);
}
int Joystick::getY(void){
  return analogRead(this->vrYPin);
}
bool Joystick::getSW(void){
  return digitalRead(this->swPin);
}
