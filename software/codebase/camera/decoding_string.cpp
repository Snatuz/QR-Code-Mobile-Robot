#include <iostream>
#include <string>
#include <vector>
#include <sstream> // Para splitString
#include <stdexcept> // Para std::invalid_argument (tratamento de erro)

// -----------------------------------------------------------------
// FUNÇÃO 1: Divisão da String (a que fizemos antes)
// -----------------------------------------------------------------

std::vector<std::string> splitString(const std::string& str, char delimiter = ',') {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        if (!token.empty()) { // Adicionado: não guarda "tokens" vazios (ex: "1,,2")
            tokens.push_back(token);
        }

// -----------------------------------------------------------------
// FUNÇÃO 2: Processador de Comandos 
// -----------------------------------------------------------------

/**
 * @brief Itera sobre o vetor de comandos e chama F e S alternadamente.
 *
 * @param comandos O vetor de strings gerado por splitString.
 */
void processarComandos(const std::vector<std::string>& comandos) {
    std::cout << "Iniciando processamento de comandos..." << std::endl;

    // Esta variável vai controlar qual função chamar.
    // true = chamar F, false = chamar S
    bool chamarFuncaoF = true;

    // Usamos um loop "for-each" para percorrer cada string no vetor
    for (const std::string& cmd : comandos) {

        // --- Passo 1: Checar o comando de parada "E" ---
        // Esta checagem DEVE vir antes da conversão para número.
        if (cmd == "E") {
            std::cout << "Comando 'E' encontrado. Fim do processamento." << std::endl;
            break; // 'break' sai do loop 'for' imediatamente.
        }

        // --- Passo 2: Tentar converter a string para um número ---
        int valorNumerico;
        try {
            // std::stoi = String To Integer (String para Inteiro)
            valorNumerico = std::stoi(cmd);

        } catch (const std::invalid_argument& e) {
            // Se o 'cmd' não for um número (ex: "abc"), std::stoi falha
            std::cerr << "ERRO: O comando '" << cmd << "' nao e um numero valido. Pulando." << std::endl;
            continue; // 'continue' pula para a próxima iteração do loop
        }

        // --- Passo 3: Chamar a função correta (F ou S) ---
        if (chamarFuncaoF) {
            forward(valorNumerico);
            usleep(500000); // Pausa de 0.5 segundos entre comandos
        } else {
            spin(valorNumerico);
            usleep(500000); // Pausa de 0.5 segundos entre comandos
        }
        // Alterna a função para a próxima iteração
        chamarFuncaoF = !chamarFuncaoF;

    } // Fim do loop 'for'

    std::cout << "Processamento de comandos concluido." << std::endl;
}
