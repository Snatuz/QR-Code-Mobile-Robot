

## Imagens com OpenCV


#### Bibliotecas:

	 <opencv2/core.hpp>:

 Como o nome sugere é o núcleo do OpenCV. Essa biblioteca fica responsável
por transformar imagens em matrizes, por isso é indispensável.

__________________________________________________________________

	<opencv2/imgcodecs.hpp>:

Principal biblioteca para lidar com imagens. Com ela é possível abrir, editar, fechar e 
salvar imagens no disco.

________________________________________________________________________

	<opencv2/highgui.hpp>:

Oferece algumas ferramentas de interface gráfica para mostrar imagens, videos e câmeras numa janela separa. Também oferece a possibilidade de vincular teclas para controlar a janela.

___________________________________

## Tipos de variáveis

	Mat:

Este tipo de variável é usado para receber a matriz de uma imagem, onde a palavra Mat se refete a palavra matriz.
________________________________________________________________________

## Funções 


	Mat cv::Imread(const string &filepath, int flags):

Essa função recebe o caminha para uma determinada imagem e retorna a matriz correspondente a ela. 

As flags são constantes definidas pela biblioteca. Ela são as seguintes:

IMREAD_COLOR -> loads the image in the BGR 8-bit format. This is the **default** that is used here.

MREAD_UNCHANGED -> loads the image as is (including the alpha channel if present)

IMREAD_GRAYSCALE -> loads the image as an intensity one
________________________________________________________________________

	samples::findFile(string archive name)

Retorna o caminho do arquivo. Ira procurar dentro do diretório onde  o arquivo que usou esta função esta para e nas subpastas deste diretório.
________________________________________________________________________

	cv::imshow(string & win_name, Mat image);

Essa função abre uma imagem numa janela com título win_name.
________________________________________________________________________


	int cv:;waitKey(int delay);

Essa função espera por uma tecla. Caso delay seja 0 ele espera à todo momento, mas caso não ele terá um determinado atraso em milissegundos.  Ele retorna o número equivalente a tecla apertada na tabela ascii.

## nota:

```C
//Use esta estrutura para conferir se a imagem foi passada como matriz //corretamente

    if(img.empty())
    {
        std::cout << "Could not read the image: " << image_path << std::endl;
        return 1;
    }
	
```


	comando de compilação geral:

g++ arquivo.cpp -o executavel_name `pkg-config --cflags --libs opencv4`
