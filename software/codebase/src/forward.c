#include "motor.h"
#include <pigpio.h>

int forward(motor user_motor) {

  motors_stop(user_motor);

  if (user_motor.velocity > RANGE)
    return 1;

  gpioPWM(user_motor.left_motor[PWM], user_motor.velocity);
  gpioPWM(user_motor.right_motor[PWM], user_motor.velocity);

  gpioWrite(user_motor.left_motor[PIN_1], 1);
  gpioWrite(user_motor.right_motor[PIN_1], 1);

  return 0;
}

void motors_stop(motor user_motor) {
  gpioPWM(user_motor.left_motor[PWM], 0);
  gpioWrite(user_motor.left_motor[PIN_1], 0);
  gpioWrite(user_motor.left_motor[PIN_2], 0);
  // garantindo que os motores estarão parados
  gpioPWM(user_motor.right_motor[PWM], 0);
  gpioWrite(user_motor.right_motor[PIN_1], 0);
  gpioWrite(user_motor.right_motor[PIN_2], 0);
}
