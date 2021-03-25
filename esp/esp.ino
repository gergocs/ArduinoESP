#include <Servo.h>

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

Servo hServo;
Servo gServo;
Servo fServo;
Servo rServo;

unsigned int psig = 0;
unsigned char x = 90;
unsigned char y = 90;
unsigned char z = 140;
bool close = true;

char received = '0';
//U - Fel
//D - Le
//F - Előre
//B - Hátra
//L - Balra
//R - Jobbra
//O - Nyit
//C - Zár

void setup() {
  pinMode(indicator, OUTPUT);
  digitalWrite(indicator, LOW);

  Serial.begin(9600);
  Serial1.begin(115200);
  while(!Serial){
  }
  while(!Serial1){
  }

  Serial.write("Ready");
  
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
  rServo.write(z);

  digitalWrite(indicator, HIGH);
}

void loop() {
  received = '0';
  if(Serial1.available()){
    received = Serial1.read();
    Serial.write(received);
  }
  if(received!='0'){
    if(received == 'U'){
      y++;
      if(y > SERVO_MAX){
        y = SERVO_MAX;
      }
    }else if(received == 'D'){
      y--;
      if(y < SERVO_MIN){
        y = SERVO_MIN;
      }
    }else if(received == 'F'){
      x++;
      if(x > SERVO_MAX){
        x = SERVO_MAX;
      }
    }else if(received == 'B'){
      x--;
      if(x < SERVO_MIN){
        x = SERVO_MIN;
      }
    }else if(received == 'L'){
      z--;
      if(z < SERVO_MIN){
        z = SERVO_MIN;
      }
    }else if(received == 'R'){
      z++;
      if(z > SERVO_MAX){
        z = SERVO_MAX;
      }
    }else if(received == 'C'){
      close = !close;
    }
  }

  if(close){
    gServo.write(opened);
  }else{
    gServo.write(closed);
  }
  rServo.write(z);
  hServo.write(y);
  fServo.write(x);
  
  delay(40);
}
