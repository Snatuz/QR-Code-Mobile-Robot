#include <iostream>
#include <pigpio.h>
#include <unistd.h>

using namespace std;

volatile int contador1 = 0;
float rpm_c1 = 0;

volatile int contador2 = 0;
float rpm_c2 = 0;

void callback1(int gpio, int level, uint32_t tick) {
  contador1++;
  rpm_c1++;
}

void callback2(int gpio, int level, uint32_t tick) {
  contador1++;
  rpm_c1++;
}

int main() {
  if (gpioInitialise() < 0) {
    cerr << "Erro ao iniciar o pigpio!" << endl;
    return 1;
  }

  int pin_e1 = 16;
  int pin_e2 = 5;

  gpioSetMode(pin_e1, PI_INPUT);
  gpioSetPullUpDown(pin_e1, PI_PUD_UP);
  gpioSetAlertFunc(pin_e1, callback1);
  gpioSetAlertFunc(pin_e2, callback2);

  cout << "Contando pulsos..." << pin_e1 << endl;

  while (true) {
    cout << "Valor atual do encoder 1: " << contador1 << endl;
    cout << "RPM atual: " << rpm_c1 / 20 << " rpm\n\n" << endl;
    cout << "Valor atual do encoder 1: " << contador2 << endl;
    cout << "RPM atual:" << rpm_c2 / 20 << "rpm" << endl;

    rpm_c1 = 0;
    rpm_c2 = 0;
    usleep(1000000);
  }

  gpioTerminate();

  return 0;
}
