//configs 

int main(){

    if (gpioInitialise() < 0) {
        std::cerr << "pigpio initialisation failed." << std::endl;
        return 1;
    }
    //-----------------------------------------------------------------
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

    usleep(50000);

//-----------------loop de busca por QR code------------------------

    while(1){
        stop();
        usleep(3000000);
        QR_search();
    }

return 0;
}
