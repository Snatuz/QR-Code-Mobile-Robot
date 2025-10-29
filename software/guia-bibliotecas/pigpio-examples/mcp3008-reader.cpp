#include <iostream>
#include <pigpio.h>
#include <spidev.h>
#include <unistd.h>

#define SPI_BUS 0  // SPI bus 0
#define SPI_DEVICE 0  // SPI device 0 (conectado ao MCP3008)

int ler_adc(int canal) {
    if (canal < 0 || canal > 7) {
        std::cerr << "Canal deve ser entre 0 e 7" << std::endl;
        return -1;
    }

    // Comando para ler o ADC
    unsigned char comando[3] = {0x01, (0x08 + canal) << 4, 0x00};
    unsigned char resposta[3];

    // Envia o comando SPI e recebe a resposta
    int handle = spiOpen(SPI_BUS, SPI_DEVICE, 1000000);
    if (handle < 0) {
        std::cerr << "Falha ao abrir o dispositivo SPI" << std::endl;
        return -1;
    }
    spiXfer(handle, comando, resposta, 3);
    spiClose(handle);

    // Calcula o valor do ADC (10 bits)
    int valor_adc = ((resposta[1] & 0x03) << 8) + resposta[2];
    return valor_adc;
}

int main() {
    // Inicializa a biblioteca pigpio
    if (gpioInitialise() < 0) {
        std::cerr << "Falha ao inicializar a biblioteca pigpio" << std::endl;
        return 1;
    }

    while (true) {
        int valor_adc = ler_adc(0);  // Lê o canal 0 do MCP3008
        std::cout << "Valor ADC do canal 0: " << valor_adc << std::endl;
        usleep(1000000);  // Espera 1 segundo
    }

    // Finaliza a biblioteca pigpio
    gpioTerminate();
    return 0;
}
