#include "motor.hpp"
#include <pigpio.h>
#include <unistd.h>

void motors_stop(motor user_motor) {
  gpioPWM(user_motor.left_motor[PWM], 0);
  gpioWrite(user_motor.left_motor[PIN_1], 0);
  gpioWrite(user_motor.left_motor[PIN_2], 0);
  // garantindo que os motores estarão parados
  gpioPWM(user_motor.right_motor[PWM], 0);
  gpioWrite(user_motor.right_motor[PIN_1], 0);
  gpioWrite(user_motor.right_motor[PIN_2], 0);
}

int forward(motor user_motor) {

  motors_stop(user_motor);

  if (user_motor.velocity > RANGE)
    return 1;

  gpioPWM(user_motor.left_motor[PWM],
          user_motor.velocity); // liga o PWM, assim como o gpioWrite liga os
                                // GPIOS. Posteriormente ele é desligado por
                                // motors_stop, que o seta para 0.
  gpioPWM(user_motor.right_motor[PWM], user_motor.velocity);

  gpioWrite(user_motor.left_motor[PIN_1], 1);
  gpioWrite(user_motor.right_motor[PIN_1], 1);
  usleep(user_motor.ftime);

  motors_stop(user_motor);
  return 0;
}
