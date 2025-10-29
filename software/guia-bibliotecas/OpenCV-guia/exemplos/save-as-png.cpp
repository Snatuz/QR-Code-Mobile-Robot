#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

int main(void) {

  string img_path = "./imagens/paisagem.jpg";
  Mat imagem = imread(img_path, IMREAD_COLOR);

  if (imagem.empty()) {
    cout << "a imagem nao foi aberta" << endl;
    return 1;
  }

  imshow("Imagem escolhida", imagem);
  int save_png = waitKey(0);

  if (save_png == 'p')
    imwrite("imagem_nova.png", imagem);

  return 0;
}
