//
// Created by Sanath Angalakudati on 2020-02-25.
//

#ifndef NSL_PAYLOAD_CONTROL
#define NSL_PAYLOAD_CONTROL
#include <Servo.h>
class Controller {
  public:
    Controller();
    void parse(unsigned char byteArray);
    void initServos();


    void _leverMove(bool up);
    bool _servoSweep(String motor, int angle);
    void _wireMove(bool up);

  private:
    //Drive Train
    void _leftDrive(bool forward);
    void _rightDrive(bool forward);
    void _leftCoast();
    void _rightCoast();



    // Pins
    int _lora_int;
    int _lora_rst;
    int _lora_cs;

    int _m1_pwm;
    int _m1_dir;
    int _m1_disable;

    int _m0_pwm;
    int _m0_dir;
    int _m0_disable;

    int _lever_nmos;
    int _lever_pwm;

    int _wire_nmos;
    int _wire_pwm;

    Servo lever;
    Servo wire;

};

#endif
