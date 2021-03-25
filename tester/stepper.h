#ifndef STEPPER_H
#define STEPPER_H 

class BipolarStepper{
  int pin1;
  int pin2;
  int pin3;
  int pin4;
  int step;
  int nextStepDelay;
  int holdTorqueDelay;
  int speed;
  const static int maxSpeed = 100;
  const static int torqueDelay = 4;
  void outputLow();
  public:
  BipolarStepper();
  BipolarStepper(int pin1, int pin2, int pin3, int pin4);
  void setSpeed(int speed);
  void update();
};

#endif
