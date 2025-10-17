#include <iostream>
#include <pigpio.h>
#include <unistd.h>

#define GPIO_PIN 18

int main() {
    // Inicializa a biblioteca pigpio
    if (gpioInitialise() < 0) {
        std::cerr << "Falha ao inicializar a biblioteca pigpio" << std::endl;
        return 1;
    }

    // Configura o pino GPIO18 como saída
    gpioSetMode(GPIO_PIN, PI_OUTPUT);

    // Configura o PWM no pino com frequência de 1kHz e ciclo de trabalho de 50%
    gpioPWM(GPIO_PIN, 128);  // 128/255 ≈ 50% de ciclo de trabalho

    // Deixa o PWM ativo por 10 segundos
    sleep(10);

    // Finaliza a biblioteca pigpio
    gpioTerminate();
    return 0;
}
