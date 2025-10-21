#include "motor.h"
#include <pigpio.h>
#include <iostream>
#include <unistd.h>

int main(void) {
    motor the_motors;

    // Configuração dos pinos (ajuste conforme seu hardware)
    the_motors.left_motor[PIN_1] = 3;
    the_motors.left_motor[PIN_2] = 5;
    the_motors.left_motor[PWM]   = 7;

    the_motors.right_motor[PIN_1] = 11;
    the_motors.right_motor[PIN_2] = 13;
    the_motors.right_motor[PWM]   = 15;

    if (gpioInitialise() < 0) {
        std::cerr << "Erro ao inicializar GPIO" << std::endl;
        return 1;
    }

    // Define pinos como saída
    gpioSetMode(3, PI_OUTPUT);
    gpioSetMode(5, PI_OUTPUT);
    gpioSetMode(7, PI_OUTPUT);
    gpioSetMode(11, PI_OUTPUT);
    gpioSetMode(13, PI_OUTPUT);
    gpioSetMode(15, PI_OUTPUT);

    // Parâmetros de movimento
    the_motors.velocity = 60;  // entre 0 e RANGE
    the_motors.theta = 90;     // giro de 90 graus
    the_motors.direction = 1;  // 1 = direita (padrão)

    for (int i = 0; i < 4; i++) {
        std::cout << "Lado " << i + 1 << std::endl;

        // Anda para frente
        forward(the_motors);
        usleep(2 * SECOND); // ajusta para o tamanho do lado desejado (2s = ~distância de um lado)
        motors_stop(the_motors);

        // Gira 90 graus à direita
        spin(the_motors);
    }

    motors_stop(the_motors);
    gpioTerminate();
    std::cout << "Trajeto concluído!" << std::endl;

    return 0;
}
