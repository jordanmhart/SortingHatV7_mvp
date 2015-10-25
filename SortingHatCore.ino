#include "Mouth.h"
Mouth mouth;

#include "Servo.h"

//Eyebrow Variables
Servo leftEyebrow; // lower=?, middle=?, upper=?
Servo rightEyebrow; // lower=?, middle=?, upper=?
Servo middleEyebrow; // lower=?, middle=?, upper=?
unsigned long leftEyebrowTimeout = 0;
unsigned long rightEyebrowTimeout = 0;
unsigned long middleEyebrowTimeout = 0;
int leftEyebrowDefault = 90;
int rightEyebrowDefault = 90;
int middleEyebrowDefault = 90;

//Eyes Variables
int redPin;
int greenPin;
int yellowPin;
int whitePin;

unsigned long redEyeTimeout = 0;
unsigned long greenEyeTimeout = 0;
unsigned long yellowEyeTimeout = 0;
unsigned long whiteEyeTimeout = 0;

unsigned long lastBlinkUpdate = 0;
bool greenEyesBlinking = false;
bool whiteEyesBlinking = false;

//Core Logic
void sort_setup() {
  Serial.begin(38400);
  mouth.setup();
  eyes_setup(11, 4, 10, 12);
  eyebrows_setup(A0, A1, A2);
  eyebrows_setLeftDefault(110);
  eyebrows_setRightDefault(130);
}
 
void sort_loop() {
  mouth.update();
  eyebrows_update();
  eyes_update();
}

void question(){
  mouth.talk(3000);
}

void thinking(){
  eyebrows_setLeftFor(140, 3000);
  eyebrows_setRightFor(100, 3000);
  eyeBlink_greenFor(3000);
  eye_whiteFor(3000);
}

void gryffindor(){
  mouth.talk(3000);
  eyebrows_setLeftFor(120, 3000);
  eyebrows_setRightFor(110, 3000);
  eye_greenFor(3000);
}

void slytherin(){
  mouth.talk(3000);
  eyebrows_setLeftFor(80, 3000);
  eyebrows_setRightFor(160, 3000);
  eye_redFor(3000);
}

void ravenclaw(){
  mouth.talk(3000);
  eyebrows_setLeftFor(140, 3000);
  eyebrows_setRightFor(100, 3000);
  eye_whiteFor(3000);
}

void hufflepuff(){
  mouth.talk(3000);
  eyebrows_setLeftFor(140, 3000);
  eyebrows_setRightFor(100, 3000);
  eye_greenFor(3000);
  eyeBlink_whiteFor(3000);
}

//void stopExpressions(){
//  mouth.stopTalking();
//}

//Eyebrow Functions
void eyebrows_setup(uint8_t leftBrowPin, uint8_t rightBrowPin, uint8_t middleBrowPin) {
  leftEyebrow.attach(leftBrowPin);
  rightEyebrow.attach(rightBrowPin);
  middleEyebrow.attach(middleBrowPin);
}

void eyebrows_update() {
  unsigned long now = millis();

  if (leftEyebrowTimeout != 0 && now > leftEyebrowTimeout) {
    eyebrows_setLeft(leftEyebrowDefault);
    leftEyebrowTimeout = 0;
  }

  if (rightEyebrowTimeout != 0 && now > rightEyebrowTimeout) {
    eyebrows_setRight(rightEyebrowDefault);
    rightEyebrowTimeout = 0;
  }

  if (middleEyebrowTimeout != 0 && now > middleEyebrowTimeout) {
    eyebrows_setMiddle(middleEyebrowDefault);
    middleEyebrowTimeout = 0;
  }
}

void eyebrows_setLeft(int pos) { leftEyebrow.write(pos); }
void eyebrows_setLeftDefault(int pos) { leftEyebrowDefault = pos; }
void eyebrows_setLeftFor(int pos, unsigned long duration) {
  leftEyebrow.write(pos);
  leftEyebrowTimeout = millis() + duration;
}

void eyebrows_setRight(int pos) { rightEyebrow.write(pos); }
void eyebrows_setRightDefault(int pos) { rightEyebrowDefault = pos; }
void eyebrows_setRightFor(int pos, unsigned long duration) {
  rightEyebrow.write(pos);
  rightEyebrowTimeout = millis() + duration;
}

void eyebrows_setMiddle(int pos) { middleEyebrow.write(pos); }
void eyebrows_setMiddleDefault(int pos) { middleEyebrowDefault = pos; }
void eyebrows_setMiddleFor(int pos, unsigned long duration) {
  middleEyebrow.write(pos);
  middleEyebrowTimeout = millis() + duration;
}

//Eyes Functions
void eyes_setup(int red, int green, int yellow, int white) {
  redPin = red;
  pinMode(redPin, OUTPUT);
  greenPin = green;
  pinMode(greenPin, OUTPUT);
  yellowPin = yellow;
  pinMode(yellowPin, OUTPUT);
  whitePin = white;
  pinMode(whitePin, OUTPUT);
}

void eyes_update() {
  unsigned long now = millis();

  if(greenEyesBlinking){
    if(now > lastBlinkUpdate + 500){
      digitalWrite(greenPin, !digitalRead(greenPin));
      lastBlinkUpdate = now;
    }
  }

  if(whiteEyesBlinking){
    if(now > lastBlinkUpdate + 500){
      digitalWrite(whitePin, !digitalRead(whitePin));
      lastBlinkUpdate = now;
    }
  }

  if (redEyeTimeout != 0 && now > redEyeTimeout) {
    digitalWrite(redPin, LOW);
    redEyeTimeout = 0;
  }

  if (greenEyeTimeout != 0 && now > greenEyeTimeout) {
    digitalWrite(greenPin, LOW);
    greenEyeTimeout = 0;
    greenEyesBlinking = false;
  }

  if (yellowEyeTimeout != 0 && now > yellowEyeTimeout) {
    digitalWrite(yellowPin, LOW);
    yellowEyeTimeout = 0;
  }

  if (whiteEyeTimeout != 0 && now > whiteEyeTimeout) {
    digitalWrite(whitePin, LOW);
    whiteEyeTimeout = 0;
    whiteEyesBlinking = false;
  }
}

void eye_redFor(unsigned long duration) {
  digitalWrite(redPin, HIGH);
  redEyeTimeout = millis() + duration;
}

void eye_greenFor(unsigned long duration) {
  digitalWrite(greenPin, HIGH);
  greenEyeTimeout = millis() + duration;
}

void eye_yellowFor(unsigned long duration) {
  digitalWrite(yellowPin, HIGH);
  yellowEyeTimeout = millis() + duration;
}

void eye_whiteFor(unsigned long duration) {
  digitalWrite(whitePin, HIGH);
  whiteEyeTimeout = millis() + duration;
}

void eyeBlink_greenFor(unsigned long duration) {
  digitalWrite(greenPin, HIGH);
  greenEyeTimeout = millis() + duration;
  lastBlinkUpdate = millis();
  greenEyesBlinking = true;
}

void eyeBlink_whiteFor(unsigned long duration) {
  digitalWrite(whitePin, HIGH);
  whiteEyeTimeout = millis() + duration;
  lastBlinkUpdate = millis();
  whiteEyesBlinking = true;
}

