#include <Servo.h>

#include "button.h"
#include "joystick.h"
#include "potentiometer.h"

#define POT_MIN 400
#define POT_MAX 600

#define SERVO_MAX 180
#define SERVO_MIN 80

#define opened 100
#define closed 30

//servos
#define high 8
#define grab 9
#define forward 10
#define rotate 11

//indicator
#define indicator 2

//joystick
#define joystickX A0
#define joystickY A1
#define pushed 6

//potentiometer
#define rotator A2

Servo hServo;
Servo gServo;
Servo fServo;
Servo rServo;

Joystick joystick(joystickX,joystickY,pushed);
Potentiometer potentiometer(rotator);

unsigned int psig = 0;
unsigned char x = 90;
unsigned char y = 90;
bool pressed = false;


/*bool open = false;
unsigned char x = 90;
unsigned char y = 90;
unsigned char rotation = 130;
*/
void setup() {
  pinMode(indicator, OUTPUT);
  digitalWrite(indicator, LOW);
  
  hServo.attach(high);
  gServo.attach(grab);
  fServo.attach(forward);
  rServo.attach(rotate);
  
  hServo.write(y);
  delay(1000);
  gServo.write(opened);
  delay(1000);
  fServo.write(x);
  delay(1000);
  rServo.write(140);

  //sync potentio meter
  while(potentiometer.getSig() < POT_MIN || potentiometer.getSig() > POT_MAX){
    delay(1000);
  }
  digitalWrite(indicator, HIGH);
}

void loop() {
  psig = analogRead(rotator);

  psig = map(psig,0,1024,0,180);
  
  if(joystick.getX() > POT_MAX){
    x++;
    if(x > SERVO_MAX){
      x = SERVO_MAX;
    }
  }else if(joystick.getX() < POT_MIN){
    x--;
    if(x < SERVO_MIN){
      x = SERVO_MIN;
    }
  }

  if(joystick.getY() > POT_MAX){
    y++;
    if(y > SERVO_MAX){
      y = SERVO_MAX;
    }
  }else if(joystick.getY() < POT_MIN){
    y--;
    if(y < SERVO_MIN){
      y = SERVO_MIN;
    }
  }
  
  rServo.write(psig);
  hServo.write(y);
  fServo.write(x);

  if(joystick.getSW()){
    gServo.write(closed);
    pressed = true;
  }
  if(!
  joystick.getSW()){
    gServo.write(opened);
    pressed = false;
  }
  
  delay(40);
}
