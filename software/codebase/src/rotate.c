#include "motor.h"
#include <math.h>
#include <pigpio.h>
#include <stdio.h>
#include <unistd.h>


static void left(motor user_motor);
static void rigth(motor user_motor);
static long int time_spin(motor user_motor);

int spin(motor user_motor) {

  if (user_motor.velocity > RANGE) {

    printf("Este valor e maior que o maximo");
    return 1;
  }

  motors_stop(user_motor);
 

  if (user_motor.direction == 1)
    rigth(user_motor);
  else // quando direction é 1, significa que o robo vai virar para direita.
    left(user_motor);

  time_spin(user_motor);
  motors_stop(user_motor);

  return 0;
}

static void left(motor user_motor) {

  gpioWrite(user_motor.left_motor[PIN_2], 1);
  gpioPWM(user_motor.left_motor[PWM], user_motor.velocity);

  gpioWrite(user_motor.left_motor[PIN_1], 1);
  gpioPWM(user_motor.left_motor[PWM], user_motor.velocity);
}

static void rigth(const motor user_motor) {

  gpioWrite(user_motor.left_motor[PIN_1], 1);
  gpioPWM(user_motor.left_motor[PWM], user_motor.velocity);

  gpioWrite(user_motor.left_motor[PIN_2], 1);
  gpioPWM(user_motor.left_motor[PWM], user_motor.velocity);
}

static long int time_spin(const motor user_motor) {

  int time;

  // isso calcula o tempo necessário para girar o angulo informado

  time = (int)((user_motor.theta * LARGE) / (user_motor.velocity * 2 * MAX_V) *
               pow(10, 6));
  usleep(time);

  return time;
}
