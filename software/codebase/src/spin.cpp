#include "motor.hpp"
#include <pigpio.h>
#include <stdio.h>
#include <unistd.h>

static void left(motor user_motor);
static void rigth(motor user_motor);
static long int time_spin(motor user_motor);

int spin(motor user_motor) {

  if (user_motor.velocity > RANGE) {

    printf("O valor de velocidade escolhido e maior do que o valor maximo "
           "determinado.");
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

// funções right (escrito rigth errôneamente) e left abaixo.

static void left(motor user_motor) {

  gpioWrite(user_motor.left_motor[PIN_2], 1);
  gpioPWM(user_motor.left_motor[PWM], user_motor.velocity);

  gpioWrite(user_motor.right_motor[PIN_1], 1);
  gpioPWM(user_motor.right_motor[PWM], user_motor.velocity);
}

static void rigth(const motor user_motor) {

  gpioWrite(user_motor.left_motor[PIN_1], 1);
  gpioPWM(user_motor.left_motor[PWM], user_motor.velocity);

  gpioWrite(user_motor.right_motor[PIN_2], 1);
  gpioPWM(user_motor.right_motor[PWM], user_motor.velocity);
}

static long int time_spin(const motor user_motor) {

  int time;

  // isso calcula o tempo necessário para girar o angulo informado.
  // o calculo de "time" veio de uma formula deduzida manualmente. As infos
  // inseridas apenas substituem as variaveis encontradas.

  time = (int)((user_motor.theta * LARGE) / (user_motor.velocity * 2 * MAX_V) *
               SECOND);
  usleep(time);

  return time;
}
