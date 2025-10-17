#include <iostream>
#include <pigpio.h>
#include <unistd.h>

#define GPIO_PIN 17

int main() {
    // Inicializa a biblioteca pigpio
    if (gpioInitialise() < 0) {
        std::cerr << "Falha ao inicializar a biblioteca pigpio" << std::endl;
        return 1;
    }

    // Configura o pino GPIO17 como entrada
    gpioSetMode(GPIO_PIN, PI_INPUT);

    // Habilita o pull-up interno (botão não pressionado será HIGH)
    gpioSetPullUpDown(GPIO_PIN, PI_PUD_UP);

    // Lê o estado do pino e imprime se o botão está pressionado
    while (true) {
        int estado = gpioRead(GPIO_PIN);
        if (estado == 0) {  // Botão pressionado (estado LOW)
            std::cout << "Botão pressionado!" << std::endl;
        }
        usleep(100000);  // Aguarda 100ms
    }

    // Finaliza a biblioteca pigpio
    gpioTerminate();
    return 0;
}

