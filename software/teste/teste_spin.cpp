/* Para teste das funcoes de spin. Basta alterar a logica para testar spin ou spin_by_ticks.*/
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

struct motor {
  
  unsigned int PWM;
  unsigned int previous_PWM = 0;
  unsigned int velocity;
  unsigned int encoder_counter = 0;
  unsigned int previous_encoder_counter = 0; 
  float error;
  float previous_error;
  float correction; 
  float derivative;
  float integral;
  
} typedef motor;


motor l_motor;
motor r_motor;
motor *left_motor = &l_motor;
motor *right_motor = &r_motor;
int distance_counter = 0;


void callback_esq(int gpio, int level, uint32_t tick) {
    left_motor->encoder_counter++;
}

void callback_dir(int gpio, int level, uint32_t tick) {
    right_motor->encoder_counter++;
    distance_counter++;
}




void stop() {
	// garantindo que os motores estar�o parados
  gpioWrite(EN1, 0);
  gpioWrite(EN2, 0);
  gpioPWM(IN1, 0);
  gpioPWM(IN2, 0);
  gpioPWM(IN3, 0);
  gpioPWM(IN4, 0);

  }
  
  

void spin_start(){
    gpioPWM(EN1, 610);
    gpioPWM(EN2, 610);
    usleep(150000);
    gpioPWM(EN1, 400);
    gpioPWM(EN2, 400);
    usleep(100000);
    gpioPWM(EN1, 370);
    gpioPWM(EN2, 370);
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
/*-------------------------------------------------------------------------------------*/

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

    usleep(50000);  // estabilização
    //------------------------------------------------------------------
    

    int vet[5];
    std::cout << "Enter 5 number of degrees to spin: ";
    for (int i=0; i<5; i++){
      std::cin >> vet[i];
      }
    
        char resposta;
    std::cout <<  "Esperar? s/n: ";
    std::cin >> resposta;
    
    if(resposta == 's'){
        usleep(30000000);}
    
    
    // Testar a função spin_by_ticks
   // std::cout << "\nGirando "<< ticks << " graus." << std::endl;
    for(int i=0; i<5; i++) {
      spin(vet[i]);
      usleep(2000000);
      }

    gpioTerminate();
    return 0;

}
