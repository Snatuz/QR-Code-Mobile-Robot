//funcao que controla a movimentacao do robo enquanto le o QR code e retorna a string lida.
std::string qr_code_data = "empty";
int QR_search() {
   
    spin(-999); //gira o robo indefinidamente pra esquerda
    distance_counter = 0;

    while(distance_counter < ???? && (qr_code_data == "empty")){ 
      qr_code_data = get_qrcode();

      usleep(50000);
    }

    if(distance_counter >= ????){
      stop();
      std::cout << "\nNao foi possivel ler o QR Code. Movimentacao interrompida." << std::endl ;
      return 0;
    }
    
    std::cout << "\nQR Code lido: " << qr_code_data << std::endl;

    stop();

    //agora voltar à direcao inicial para executar os comandos
    //preciso passar os ticks contados para a funcao spin_by_ticks, mas uso o
    //mesmo contador de distancia (distance_counter) para isso, entao salvo o valor
    //em outra variavel temporaria
    int temp_distance = -distance_counter;
    spin_by_ticks(temp_distance); //gira o robo de volta à posicao inicial


    //hora de processar o QR code lido

    std::vector<std::string> comands = splitString(qr_code_data);
    processarComandos(comands);


    return 0;
    
}
