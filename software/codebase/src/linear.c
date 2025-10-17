#include "motor.h"
#include <pigpio.h>

void motors_stop(const motor user_motor) {
  gpioPWM(user_motor.left_motor[PWM], 0);
  gpioWrite(user_motor.left_motor[PIN_1], 0);
  gpioWrite(user_motor.left_motor[PIN_2], 0);
  // garantindo que os motores estarão parados
  gpioPWM(user_motor.rigth_motor[PWM], 0);
  gpioWrite(user_motor.rigth_motor[PIN_1], 0);
  gpioWrite(user_motor.rigth_motor[PIN_2], 0);
}
