#include <Stepper.h>

const int stepsPerRevolution = 200;
Stepper stepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  stepper.setSpeed(100);

}

void loop() {
  stepper.step(stepsPerRevolution);

}
