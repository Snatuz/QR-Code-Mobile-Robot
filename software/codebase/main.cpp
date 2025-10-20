#include "motor.h"
#include <iostream>
#include <pigpio.h>

int main(void) {

  motor the_motors;

  std::cout << "escolha o angulo, velocida e lado que o robo ira se mover\n\n";

  std::cin.get();
  std::cout << "angulo";
  std::cin >> the_motors.theta;
  std::cout << std::endl << "velocidade";
  std::cin >> the_motors.velocity;
  std::cout << std::endl << "lado";
  std::cin >> the_motors.direction;

  if (gpioInitialise() < 0) {

    std::cerr << "erro";
  }

  // so falta configurar a pinagem aqui.

  spin(the_motors);

  return 0;
}
