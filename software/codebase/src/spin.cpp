#include "motor.hpp"
#include <pigpio.h>
#include <iostream>
#include <unistd.h>

int distance_counter = 0;

void spin_start(){
    gpioPWM(EN1, 500);
    gpioPWM(EN2, 500);
    usleep(200000);
    gpioPWM(EN1, 400);
    gpioPWM(EN2, 400);
    usleep(100000);
    gpioPWM(EN1, 300);//pwm finais a serem testados empiricamente
    gpioPWM(EN2, 300);
}


int spin (int angle) {
  
  stop();
  
  if(angle > 0){ //girar para a direita
    gpioWrite(IN1, 1);
    gpioWrite(IN2, 0);
    gpioWrite(IN3, 0);
    gpioWrite(IN4, 1);
  }
  else{ //girar para a esquerda
    gpioWrite(IN1, 0);
    gpioWrite(IN2, 1);
    gpioWrite(IN3, 1);
    gpioWrite(IN4, 0);
  }

    if (angle > 360 && angle != 999)  {
    std::cout << "\nvoce inseriu um angulo inadequado, entao esse comando nao foi executado. Prosseguindo...\n";
    return 0;
  }

    if (angle < -360 && angle != -999) {
    std::cout << "\nvoce inseriu um angulo inadequado, entao esse comando nao foi executado. Prosseguindo...\n";
    return 0;
  }
  //funcoes spin com angulo indeterminado
  if(angle == 999){
    spin_start();
    return 0;
  }

  if(angle == -999){
    spin_start();
    return 0;
  }
  
  angle = angle < 0 ? -angle : angle; //transforma em positivo

  spin_start();

  distance_counter = 0;
  while(distance_counter < (angle / 6.3)){
    usleep(100000);
  }
  
  stop();
  return 0;
}


int spin_by_ticks(int ticks) {
    stop();

    if (ticks > 0) { // girar para a direita
        gpioWrite(IN1, 1);
        gpioWrite(IN2, 0);
        gpioWrite(IN3, 0);
        gpioWrite(IN4, 1);
    } else { // girar para a esquerda
        gpioWrite(IN1, 0);
        gpioWrite(IN2, 1);
        gpioWrite(IN3, 1);
        gpioWrite(IN4, 0);
    }

    ticks = ticks < 0 ? -ticks : ticks; // transforma em positivo

    spin_start();

    distance_counter = 0;
    while (distance_counter < ticks) {
        usleep(100000);
    }

    stop();
    return 0;
}
