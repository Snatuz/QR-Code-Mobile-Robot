#include "camera.hpp"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp> // QRCodeDetector
#include <opencv2/videoio.hpp>

static std::string get_qrcode();

  // funcao que controla a movimentacao do robo enquanto le o QR code e retorna
  // a string lida.
  std::string qr_code_data;

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
      exit(0);
    }

    std::cout << "\nQR Code lido: " << qr_code_data << std::endl;

    stop();
    usleep(1000000);

    int temp_distance = -distance_counter;
    spin_by_ticks(temp_distance); // gira o robo de volta à posicao inicial

    // hora de processar o QR code lido

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
