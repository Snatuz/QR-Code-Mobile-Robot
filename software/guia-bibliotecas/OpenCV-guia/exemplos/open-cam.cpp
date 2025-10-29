
#include <iostream>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <thread>

using namespace cv;
using namespace std;

Mat ultimoFrame;
mutex frameMutex;
bool run = true;

// Thread de captura de vídeo
void capturaThread(VideoCapture &camera) {
  Mat frame;
  while (run) {
    camera >> frame;
    if (frame.empty())
      continue;

    lock_guard<mutex> lock(frameMutex);
    ultimoFrame = frame.clone(); // copia segura do frame
  }
}

int main() {
  VideoCapture camera(2); // abre a primeira webcam
  if (!camera.isOpened()) {
    cerr << "Erro ao abrir a câmera!" << endl;
    return -1;
  }

  // inicia a thread de captura
  thread t(capturaThread, ref(camera));

  while (true) {
    Mat frameLocal;
    {
      lock_guard<mutex> lock(frameMutex);
      if (!ultimoFrame.empty())
        frameLocal = ultimoFrame.clone();
    }

    if (!frameLocal.empty())
      imshow("Webcam", frameLocal);

    int key = waitKey(1);
    if (key == 27)
      break;               // ESC para sair
    else if (key == 's') { // 's' para capturar
      imshow("Captura", frameLocal);
    }
  }

  run = false; // sinaliza para a thread parar
  t.join();    // espera a thread terminar
  camera.release();
  destroyAllWindows();
  return 0;
}
