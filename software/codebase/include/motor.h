#ifndef MOTOR_H
#define MOTOR_H

#include <stdio.h>

#define RANGE 100
#define PWM 3
#define PIN_1
#define PIN_1
#define LARGE                                                                  \
  10 // isso a distancia de uma roda até a outra, isso deve ser adaptado para
     // realidade;

#ifdef __cplusplus
extern "C" { // para compatibilidade com o C++
#endif

const double real_max_velocity = 0.47645;

struct motor {

  unsigned short int direction;
  unsigned int
      left_motor[2]; // left_motor e right_motor são os pinos que ligam o motor
  unsigned int right_motor[2]; // na ponte h, sendo dois para define direção e
                               // uma para pwm
  unsigned int theta;
  unsigned int velocity; // o pwm a ser usado nos moteres
} typedef motor;

void spin(const motor user_motor);

void motors_stop(const motor user_motor);

#ifdef __cplusplus
}
#endif

#endif
