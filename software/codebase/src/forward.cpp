#include "motors.hpp"
#include <pigpio.h>
#include <unistd.h>
#include <iostream>

int distance_counter = 0;

void forward (int distance) {
  
  stop();
  gpioWrite(IN1, 1);
  gpioWrite(IN3, 1);
  gpioPWM(EN1, 500);
  gpioPWM(EN2, 500); //definir empiricamente o valor que faz o robo andar reto
  
  distance_counter = 0;
  while(distance_counter < distance){  //pois 1 tick do encoder = APROX. 1 cm 
    usleep(100000);
  }
  
  stop();

}

