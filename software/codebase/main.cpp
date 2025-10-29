#include "motor.hpp"
#include <iostream>
#include <pigpio.h>
#include <unistd.h>

int main(void) {
  motor the_motors;

  // CONFIGURAÇÃO DOS PINOS (ajuste conforme seu hardware)
  the_motors.left_motor[PIN_1] = 2;
  the_motors.left_motor[PIN_2] = 3;
  the_motors.left_motor[PWM] = 12;

  the_motors.right_motor[PIN_1] = 27;
  the_motors.right_motor[PIN_2] = 17;
  the_motors.right_motor[PWM] = 13;

  if (gpioInitialise() < 0) {
    std::cerr << "Erro ao inicializar GPIO" << std::endl;
    return 1;
  }

  gpioSetPWMrange(the_motors.left_motor[PWM], RANGE);
  gpioSetPWMrange(the_motors.right_motor[PWM],
                  RANGE); // setando o range do PWM para 100.

  // DEFINIÇÕES DE ENTRADAS E SAÍDAS
  gpioSetMode(2, PI_OUTPUT);
  gpioSetMode(3, PI_OUTPUT);
  gpioSetMode(12, PI_OUTPUT);
  gpioSetMode(13, PI_OUTPUT);
  gpioSetMode(17, PI_OUTPUT);
  gpioSetMode(27, PI_OUTPUT);

  // Parâmetros de movimento
  the_motors.velocity = 60;      // entre 0 e RANGE
  the_motors.theta = 90;         // giro de 90 graus
  the_motors.direction = 1;      // 1 = direita (padrão)
  the_motors.ftime = 2 * SECOND; // anda por dois segundos

  for (int i = 0; i < 4; i++) {
    std::cout << "Lado " << i + 1 << std::endl;

    // Anda para frente
    forward(the_motors);
    usleep(100000);
    motors_stop(the_motors);

    // Gira 90 graus à direita
    spin(the_motors);
  }

  motors_stop(the_motors);
  gpioTerminate();
  std::cout << "Trajeto concluído!" << std::endl;

  return 0;
}
