#include <iostream>
#include <pigpio.h>
#include <unistd.h>

#define GPIO_PIN 17

int main() {

  if (gpioInitialise() < 0) {
    std::cerr << "Falha ao inicializar a biblioteca pigpio" << std::endl;
    return 1;
  }

  gpioSetMode(GPIO_PIN, PI_OUTPUT);

  for (int i = 0; i < 10; i++) {
    gpioWrite(GPIO_PIN, 1);
    usleep(1000000);
    gpioWrite(GPIO_PIN, 0);
    usleep(1000000);
  }

  gpioTerminate();

  return 0;
}
