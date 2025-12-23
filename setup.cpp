#include <iostream>
#include <string.h>
#include <vector>
#include <sstream> // Para splitString
#include <stdexcept> // Para std::invalid_argument (tratamento de erro)
#include <pigpio.h>
#include <unistd.h>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp> // QRCodeDetector
#include <opencv2/videoio.hpp>

#define pinencoder_esq 7
#define pinencoder_dir 8
#define IN1 2
#define IN2 3
#define IN3 17
#define IN4 27
#define EN1 4  
#define EN2 22

//--------------------------------------------------------------------------------//
                        //PROTOTIPOS DE FUNÇÕES
int spin(int angle);
void callback_esq(int gpio, int level, uint32_t tick);
void callback_dir(int gpio, int level, uint32_t tick);
void spin_start();
void stop();
void forward(int distance);
void spin_by_ticks(int ticks);
std::vector<std::string> splitString(const std::string& str, char delimiter = ',');
void processarComandos(const std::vector<std::string>& comandos);
int QR_search();
static std::string get_qrcode();

//--------------------------------------------------------------------------------//        
                            //DECLARACAO DE VARIAVEIS
int distance_counter = 0;
std::string qr_code_data;
//--------------------------------------------------------------------------------//
                            //STRUCTS

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
float KP = 0;
float KI = 0;
float KD = 0;
float setpoint = 0;

//--------------------------------------------------------------------------------//
                        //FUNCOES

void forward (int distance) {
  
  stop();
  gpioWrite(IN1, 1);
  gpioWrite(IN3, 1);
  gpioPWM(EN1, 530);
  gpioPWM(EN2, 500); //definir empiricamente o valor que faz o robo andar reto
  
  distance_counter = 0;
  while(distance_counter < distance){  //pois 1 tick do encoder = APROX. 1 cm 
    usleep(100000);
  }
  stop();
}

void stop() {
  gpioWrite(EN1, 0);
  gpioWrite(EN2, 0);
  gpioPWM(IN1, 0);
  gpioPWM(IN2, 0);
  gpioPWM(IN3, 0);
  gpioPWM(IN4, 0);
  }


void callback_esq(int gpio, int level, uint32_t tick) {
    left_motor->encoder_counter++;
}

void callback_dir(int gpio, int level, uint32_t tick) {
    right_motor->encoder_counter++;
    distance_counter++;
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


std::vector<std::string> splitString(const std::string& str, char delimiter = ',') {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        if (!token.empty()) { 
            tokens.push_back(token);
        }
    }
    return tokens;
}



void processarComandos(const std::vector<std::string>& comandos) {
    std::cout << "Iniciando processamento de comandos..." << std::endl;

    bool chamarFuncaoF = true;

  
    for (const std::string& cmd : comandos) {

       
        if (cmd == "E") {
            std::cout << "Comando 'E' encontrado. Fim do processamento." << std::endl;
            exit(0);
        }

      //  converter a string para um número
        int valorNumerico;
        try {
            
            valorNumerico = std::stoi(cmd);

        } catch (const std::invalid_argument& e) {
            
            std::cerr << "ERRO: O comando '" << cmd << "' nao e um numero valido. Pulando." << std::endl;
            continue; 
        }

        if (chamarFuncaoF) {
            forward(valorNumerico);
            usleep(500000); // Pausa de 0.5 segundos    
        } else {
            spin(valorNumerico);
            usleep(500000); // Pausa de 0.5 segundos
        }
       
        chamarFuncaoF = !chamarFuncaoF;

    } 

    std::cout << "Processamento de comandos concluido." << std::endl;
}



int QR_search() {

    qr_code_data = "empty";
    VideoCapture cam(0);
    spin(-999); // gira o robo indefinidamente pra esquerda
    distance_counter = 0;

    while(distance_counter < 171 && (qr_code_data == "empty")){
      qr_code_data = get_qrcode();

      usleep(50000);
    }

    if(distance_counter >= 171){
      stop();
      std::cout
          << "\nNao foi possivel ler o QR Code. Movimentacao interrompida."
          << std::endl;
      exit(0); // quebra a execucao do codigo
    }

    std::cout << "\nQR Code lido: " << qr_code_data << std::endl;

    stop();
    usleep(1000000);

    int temp_distance = -distance_counter;
    spin_by_ticks(temp_distance); // gira o robo de volta à posicao inicial

    std::vector<std::string> comands = splitString(qr_code_data);
    processarComandos(comands);

    return 0;
  }

  using namespace cv;


static std::string get_qrcode() {

    if (!cam.isOpened())
      return "erro ao abrir a camera";

    QRCodeDetector qr;
    Mat frame;
    cam >> frame;
    if (frame.empty())
      return "empty";

    std::vector<Point> bbox;
    std::string data = qr.detectAndDecode(frame, bbox);

    return data.empty() ? "empty" : data;
  }


//*******************
 
