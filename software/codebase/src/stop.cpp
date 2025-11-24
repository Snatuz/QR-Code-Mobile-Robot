#include "motor.hpp"
#include <pigpio.h>
#include <unistd.h>

void stop() {
	// garantindo que os motores estar�o parados
  gpioWrite(EN1, 0);
  gpioWrite(EN2, 0);
  gpioPWM(IN1, 0);
  gpioPWM(IN2, 0);
  gpioPWM(IN3, 0);
  gpioPWM(IN4, 0);

  }
