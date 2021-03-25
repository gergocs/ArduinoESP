#include <Arduino.h>
#include "stepper.h"

BipolarStepper::BipolarStepper() {

}

BipolarStepper::BipolarStepper(int pin1, int pin2, int pin3, int pin4):
  pin1(pin1), pin2(pin2), pin3(pin3), pin4(pin4),
  step(0), nextStepDelay(0), speed(0) {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);
  outputLow();
}

void BipolarStepper::outputLow()
{
  digitalWrite(pin1, LOW);
  digitalWrite(pin2, LOW);
  digitalWrite(pin3, LOW);
  digitalWrite(pin4, LOW);
}

void BipolarStepper::setSpeed(int speed)
{
  if (abs(speed) <= maxSpeed)
  {
    this->speed = speed;
  }
  else if(speed < -100){
    this->speed = -100;
  }
  else if(speed > 100){
    this->speed = 100;
  }
  nextStepDelay = 0;
  holdTorqueDelay = torqueDelay;
}

void BipolarStepper::update()
{

  if (speed == 0) {
    outputLow();
  }
  else {
    nextStepDelay--;
    
    if (holdTorqueDelay > 0) {
      holdTorqueDelay--;
      if (holdTorqueDelay <= 0) {
        outputLow();
      }
    }
    
    if (nextStepDelay <= 0)
    {
      if (speed < 0)
      {
        step--;
      }
      else if (speed > 0)
      {
        step++;
      }

      if (step < 0)
      {
        step = 3;
      }
      else if (step > 3)
      {
        step = 0;
      }

      outputLow();
      switch (step)
      {
        case 0:
          digitalWrite(pin1, HIGH);
          digitalWrite(pin2, HIGH);
          break;
        case 1:
          digitalWrite(pin2, HIGH);
          digitalWrite(pin3, HIGH);
          break;
        case 2:
          digitalWrite(pin3, HIGH);
          digitalWrite(pin4, HIGH);
          break;
        case 3:
          digitalWrite(pin4, HIGH);
          digitalWrite(pin1, HIGH);
          break;
      }
      nextStepDelay = maxSpeed - abs(speed) + 2;
      holdTorqueDelay = torqueDelay;
      delay(nextStepDelay+1);
    }
  }
}
