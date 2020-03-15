#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#include "pins_arduino.h"
#endif

#include "controller.h"
#include <Servo.h>
#include <string.h>


Controller::Controller(){

  //Pin Set
  _lora_int = 0;
  _lora_rst = 1;
  _lora_cs = 10;

  _m0_pwm = 5;
  _m0_dir = 6;
  _m0_disable = 7;

  _m1_pwm = 2;
  _m1_dir = 3;
  _m1_disable = 4;

  _wire_nmos = 23;
  _wire_pwm = 24;

  _lever_nmos = 21;
  _lever_pwm = 22;

 //Motor Init
 pinMode(_m0_pwm, OUTPUT);
 pinMode(_m0_dir, OUTPUT);
 pinMode(_m0_disable, OUTPUT);

 pinMode(_m1_pwm, OUTPUT);
 pinMode(_m1_dir, OUTPUT);
 pinMode(_m1_disable, OUTPUT);

 //Servo Init
 Servo wire = Servo();
 wire.attach(_wire_pwm);


 Servo lever = Servo();
 lever.attach(_lever_pwm);

}

void Controller::initServos() {
  digitalWrite(_wire_nmos, HIGH);
  delay(100);

  digitalWrite(_lever_nmos, HIGH);
  delay(100);

  wire.write(45);
  delay(20);
  wire.write(45);
  delay(20);
}

/*
PARSE: The Main function that recieves char[] and calls appropriate functions
Bit 1: Left On/Off
Bit 2: Left Forward/Backwards
Bit 3: Right On/Off
Bit 4: Right Forward/Backwards
Bit 5: Lever On/Off
Bit 6: Lever Forwards/Backwards
Bit 7: Wire On/Off
Bit 8: Wire Forwards/Backwards
// 0x41 is the magic number

*/
void Controller::parse(unsigned char signal) {
  //Left Motor
  if (signal & 0x01) {
    signal >>= 1;
    bool forwards = (signal & 0x01);
    _leftDrive(forwards);
  } else {
    _leftCoast();
    signal >>= 2;
  }

  //Right Motor
  if (signal & 0x01) {
    signal >>= 1;
    bool forwards = (signal & 0x01);
    _rightDrive(forwards);
  } else {
    _rightCoast();
    signal >>= 2;
  }

  //Lever
  if (signal & 0x01) {
    signal >>= 1;
    bool forwards = (signal & 0x01);
    _leverMove(forwards);
  } else {
    signal >>= 2;
  }

  //Wire
  if (signal & 0x01) {
    signal >>= 1;
    bool forwards = (signal & 0x01);
    _wireMove(forwards);
  } else {
    signal >>= 2;
  }

}

void Controller::_leftDrive(bool forwards){
  if(forwards){
    digitalWrite(_m0_dir, HIGH);
    digitalWrite(_m0_disable, HIGH);
    analogWrite(_m0_pwm, 255);
  } else {
    digitalWrite(_m0_dir, LOW);
    digitalWrite(_m0_disable, HIGH);
    analogWrite(_m0_pwm, 255);
  }
  return;
}

void Controller::_rightDrive(bool forwards){
  if(forwards){
    digitalWrite(_m1_dir, HIGH);
    digitalWrite(_m1_disable, HIGH);
    analogWrite(_m1_pwm, 255);
  } else {
    digitalWrite(_m1_dir, LOW);
    digitalWrite(_m1_disable, HIGH);
    analogWrite(_m1_pwm, 255);
  }
  return;
}

void Controller::_leftCoast(){
  digitalWrite(_m0_disable, LOW);
}

void Controller::_rightCoast() {
  digitalWrite(_m1_disable, LOW);
}

void Controller::_leverMove(bool up){
  int angle = lever.read();
  if (up) {
    if (angle >= 175) return;
    lever.write(angle + 5);
    delay(10);
  } else {
    if (angle <= 5) return;
    lever.write(angle - 5);
    delay (10);
  }
}

void Controller::_wireMove(bool up) {
  int angle = wire.read();
  if (up) {
    if (angle >= 175) return;
    wire.write(angle + 5);
    delay(10);
  } else {
    if (angle <= 5) return;
    wire.write(angle - 5);
    delay (10);
  }
}
bool Controller::_servoSweep(String motor, int dest){
  if (motor.equals("lever")) {
    int current = lever.read();
    for (; current < dest; current++) {
      lever.write(dest);
    }
    return true;

  } else if(motor.equals("wire")) {
    int current = lever.read();
    for (; current < dest; current++) {
      lever.write(dest);
    }
    return true;
  }
  return false;
}
