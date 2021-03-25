#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

class Potentiometer{
  public:
    Potentiometer(void);
    Potentiometer(int pin);
    int getSig(void);
  private:
    int pin;
};

#endif
