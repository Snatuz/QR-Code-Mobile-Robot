#include "motor.h"
#include <math.h>
#include <pigpio.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

static void left(motor user_motor);
static void rigth(motor user_motor);
static long int time_spin(const motor user_motor);

void spin(const motor user_motor) {

  if (velocity > RANGE) {

    sprintf(stderr, "Este valor e maior que o maximo");
    return 1;
  }

  motors_stop(const motor user_motor);
  gpioSetPWMrange(unsigned int user_motor, RANGE);

  if (direction = 1)
    rigth(user_motor);
  else // quando direction é true, significa que o robo vai virar para direita.
    left(user_motor);

  time_spin(const int user_motor);
  motors_stop();
}

static void left(const motor user_motor) {

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

  time[0] = (int)((user_motor.theta * LARGE) /
                  (user_motor.velocity * 2 * real_max_velocity) * pow(10, 6));

  usleep(time);
  usleep(time);

  return time;
}
