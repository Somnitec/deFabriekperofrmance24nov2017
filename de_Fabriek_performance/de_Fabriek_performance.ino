#include <Servo.h>

#define potmeter A5
#define organ1 A0
#define organ2 A1

#define servoson A2
#define organfull 11

int timemod = 100;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int pos1 = 0;
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;
unsigned long postimer1 = 0;
unsigned long postimer2 = 0;
unsigned long postimer3 = 0;
unsigned long postimer4 = 0;
int pos1time = 7;
int pos2time = 8;
int pos3time = 9;
int pos4time = 10;
float pos1ratio = 0.8;
float pos2ratio = 0.8;
float pos3ratio = 0.8;
float pos4ratio = 0.8;
int posmin = 0;
int posmax = 30;


boolean organ1state = false;
int organ1ontime = 7;
int organ1offtime = 2;
unsigned long organ1timer = 0;


boolean organ2state = true;
int organ2ontime = 3;
int organ2offtime = 7;
unsigned long organ2timer = 0;



int states = 4;

void setup() {

  //setup servos
  servo1.attach(5);
  servo2.attach(6);
  servo3.attach(9);
  servo4.attach(10);

  servo1.write(pos1);
  servo2.write(pos2);
  servo3.write(pos3);
  servo4.write(pos4);

  //setup potmeter
  pinMode(potmeter, INPUT);
  pinMode(A4, OUTPUT);
  digitalWrite(A4, LOW);
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);

  //setup relays
  pinMode(organ1, OUTPUT);
  pinMode(organ2, OUTPUT);

  pinMode(servoson,INPUT_PULLUP);
  pinMode(organfull,INPUT_PULLUP);

  Serial.begin(115200);
  Serial.println("restarted!");
}

void loop() {
  generator();
}

void generator() {
  timemod=analogRead(potmeter);
  if(digitalRead(organfull))organs();
  else {
    digitalWrite(organ1, HIGH);
    digitalWrite(organ2, HIGH);
  }
  if(digitalRead(servoson))  servos();


}

void organs() {
  unsigned long currentMillis = millis();

  if (organ1state) {
    if (currentMillis - organ1timer > organ1ontime*timemod) {
      organ1timer = currentMillis;
      organ1state = false;
      digitalWrite(organ1, organ1state);
    }
  }  else {
    if (currentMillis - organ1timer > organ1offtime*timemod) {
      organ1timer = currentMillis;
      organ1state = true;
      digitalWrite(organ1, organ1state);
    }
  }

  if (organ2state) {
    if (currentMillis - organ2timer > organ2ontime*timemod) {
      organ2timer = currentMillis;
      organ2state = false;
      digitalWrite(organ2, organ2state);
    }
  }  else {
    if (currentMillis - organ2timer > organ2offtime*timemod) {
      organ2timer = currentMillis;
      organ2state = true;
      digitalWrite(organ2, organ2state);
    }
  }
}

void servos() {
  unsigned long currentMillis = millis();

  if (pos1 == posmin) {
    if (currentMillis - postimer1 > timemod*pos1time*pos1ratio) {
      postimer1 = currentMillis;
      pos1 = posmax;
    }
  }  else {
    if (currentMillis - postimer1 > timemod*pos1time*(1-pos1ratio)) {
      postimer1 = currentMillis;
      pos1 = posmin;
    }
  }
  if (pos2 == posmin) {
    if (currentMillis - postimer2 > timemod*pos2time*pos2ratio) {
      postimer2 = currentMillis;
      pos2 = posmax;
    }
  }  else {
    if (currentMillis - postimer2 > timemod*pos2time*(1-pos2ratio)) {
      postimer2 = currentMillis;
      pos2 = posmin;
    }
  }
  if (pos3 == posmin) {
    if (currentMillis - postimer3 > timemod*pos3time*pos3ratio) {
      postimer3 = currentMillis;
      pos3 = posmax;
    }
  }  else {
    if (currentMillis - postimer3 > timemod*pos3time*(1-pos3ratio)) {
      postimer3 = currentMillis;
      pos3 = posmin;
    }
  }
  if (pos4 == posmin) {
    if (currentMillis - postimer4 > timemod*pos4time*pos4ratio) {
      postimer4 = currentMillis;
      pos4 = posmax;
    }
  }  else {
    if (currentMillis - postimer4 > timemod*pos4time*(1-pos4ratio)) {
      postimer4 = currentMillis;
      pos4 = posmin;
    }
  }
  //Serial.println(pos1);
  servo1.write(pos1);
  servo2.write(pos2);
  servo3.write(pos3);
  servo4.write(pos4);
}

