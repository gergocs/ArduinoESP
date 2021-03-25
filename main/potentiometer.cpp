#include <Arduino.h>

#include "potentiometer.h"

Potentiometer::Potentiometer(void){
  this->pin = 0;
}
Potentiometer::Potentiometer(int pin){
  this->pin = pin;
}
int Potentiometer::getSig(void){
  return analogRead(this->pin);
}
