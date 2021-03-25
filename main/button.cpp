#include <Arduino.h>

#include "button.h"

Button::Button(void){
  this->pin = 0;
  this->sig = 0;
}
Button::Button(int pin){
  this->pin = pin;
  pinMode(pin, INPUT);
}
bool Button::getSig(void){
  return digitalRead(pin);
}
