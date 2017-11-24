#include <Servo.h>

#define potmeter A5
#define organ1 A0
#define organ2 A1

int bpm = 80;

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

int pos1 = 0;
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;
int pos5 = 0;
int pos6 = 0;

unsigned long postimer = 0;
int posmin = 0;
int posmax = 10;

boolean organ1state = false;
int organ1ontime = 100;
int organ1offtime = 200;
unsigned long organ1timer = 0;

boolean organ2state = true;
int organ2ontime = 300;
int organ2offtime = 400;
unsigned long organ2timer = 0;

void setup() {

  //setup servos
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
  servo5.attach(10);
  servo6.attach(11);

  servo1.write(pos1);
  servo2.write(pos2);
  servo3.write(pos3);
  servo4.write(pos4);
  servo5.write(pos5);
  servo6.write(pos6);

  //setup potmeter
  pinMode(potmeter, INPUT);
  pinMode(A4, OUTPUT);
  digitalWrite(A4, LOW);
  pinMode(A3, OUTPUT);
  digitalWrite(A3, HIGH);

  //setup relays
  pinMode(organ1, OUTPUT);
  pinMode(organ2, OUTPUT);

  Serial.begin(115200);
  Serial.println("restarted!");
}

void loop() {
  generator();
}

void generator() {
  organs();
  //servos();
  //Serial.println(analogRead(potmeter));

  delay(10);
}

void organs() {
  unsigned long currentMillis = millis();

  if (organ1state) {
    if (currentMillis - organ1timer > organ1ontime) {
      organ1timer = currentMillis;
      organ1state = false;
      digitalWrite(organ1, organ1state);
    }
  }  else {
    if (currentMillis - organ1timer > organ1offtime) {
      organ1timer = currentMillis;
      organ1state = true;
      digitalWrite(organ1, organ1state);
    }
  }

  if (organ2state) {
    if (currentMillis - organ2timer > organ2ontime) {
      organ2timer = currentMillis;
      organ2state = false;
      digitalWrite(organ2, organ2state);
    }
  }  else {
    if (currentMillis - organ2timer > organ2offtime) {
      organ2timer = currentMillis;
      organ2state = true;
      digitalWrite(organ2, organ2state);
    }
  }
}

void servos() {
  unsigned long currentMillis = millis();

  if (pos1 == posmin) {
    if (currentMillis - postimer > 500) {
      postimer = currentMillis;
      pos1 = posmax;
      pos2 = posmax;
      pos3 = posmax;
      pos4 = posmax;
      pos5 = posmax;
      pos6 = posmax;
    }
  }  else {
    if (currentMillis - postimer > 500) {
      postimer = currentMillis;
      pos1 = posmin;
      pos2 = posmin;
      pos3 = posmin;
      pos4 = posmin;
      pos5 = posmin;
      pos6 = posmin;
    }
  }
  Serial.println(pos1);
  servo1.write(pos1);
  servo2.write(pos2);
  servo3.write(pos3);
  servo4.write(pos4);
  servo5.write(pos5);
  servo6.write(pos6);
}

