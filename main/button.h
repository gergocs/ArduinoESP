#ifndef BUTTON_H
#define BUTTON_H

class Button{
  public:
    Button(void);
    Button(int pin);
    bool getSig(void);
  private:
    int pin;
    bool sig;
};

#endif
