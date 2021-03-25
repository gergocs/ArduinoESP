#ifndef JOYSTICK_H
#define JOYSTICK_H

class Joystick{
  public:
    Joystick(void);
    Joystick(int vrXPin, int vrYPin, int swPin);
    int getX(void);
    int getY(void);
    bool getSW(void);
  private:
    int vrXPin;
    int vrYPin;
    int swPin;
};

#endif
