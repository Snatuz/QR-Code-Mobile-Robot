#include "motors.hpp"
#include <iostream>
#include <pigpio.h>
#include <unistd.h>
#include <cstdint>

#define pinencoder_esq 7
#define pinencoder_dir 8
#define IN1 2
#define IN2 3
#define IN3 17
#define IN4 27
#define EN1 4     //criar funcao setup() depois
#define EN2 22



uint32_t tick_anterior = 0;
uint32_t intervalo = 0;




void callback_esq(int gpio, int level, uint32_t tick) {
    left_motor->encoder_counter++;
}

void callback_dir(int gpio, int level, uint32_t tick) {
    right_motor->encoder_counter++;
    distance_counter++;
}


    gpioSetPWMrange(EN1, 1000);
    gpioSetPWMrange(EN2, 1000);

    gpioSetMode(pinencoder_esq, PI_INPUT);
    gpioSetMode(pinencoder_dir, PI_INPUT);
    gpioSetMode(IN1, PI_OUTPUT);
    gpioSetMode(IN2, PI_OUTPUT);
    gpioSetMode(IN3, PI_OUTPUT);
    gpioSetMode(IN4, PI_OUTPUT);
    gpioSetMode(EN1, PI_OUTPUT);
    gpioSetMode(EN2, PI_OUTPUT);

    gpioSetPullUpDown(pinencoder_esq, PI_PUD_UP);
    gpioSetPullUpDown(pinencoder_dir, PI_PUD_UP);

    gpioSetAlertFunc(pinencoder_esq, callback_esq);
    gpioSetAlertFunc(pinencoder_dir, callback_dir);

    usleep(50000);  // estabilização
