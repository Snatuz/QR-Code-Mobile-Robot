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
    }
    return tokens;
}

// -----------------------------------------------------------------
// FUNÇÕES DE EXEMPLO (F e S)
// -----------------------------------------------------------------
// Elas recebem um 'int'. Note que o vetor guarda 'string',
// então teremos que converter de "90" (string) para 90 (int).

/**
 * @brief Função 'F' (ex: mover para frente/trás)
 */
void F(int valor) {
    std::cout << "  -> Chamando F(int) com valor: " << valor << std::endl;
    // Coloque sua lógica real aqui (ex: comandoMotor(valor);)
}

/**
 * @brief Função 'S' (ex: girar servo)
 */
void S(int valor) {
    std::cout << "  -> Chamando S(int) com valor: " << valor << std::endl;
    // Coloque sua lógica real aqui (ex: comandoServo(valor);)
}


// -----------------------------------------------------------------
// FUNÇÃO 2: Processador de Comandos (A NOVA LÓGICA)
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
            F(valorNumerico);
        } else {
            S(valorNumerico);
        }

        // --- Passo 4: Alternar a próxima função ---
        // Inverte o valor do booleano (true vira false, false vira true)
        chamarFuncaoF = !chamarFuncaoF;

    } // Fim do loop 'for'

    std::cout << "Processamento de comandos concluido." << std::endl;
}


// --- Função principal (main) para testar tudo ---
int main() {
    // String vinda do QR Code (exemplo 1)
    std::string qrCodeData1 = "1,90,2,-90,E,100,200"; // O "100" e "200" serão ignorados

    std::cout << "--- Teste 1 ---" << std::endl;
    std::vector<std::string> vetorDeComandos1 = splitString(qrCodeData1);
    processarComandos(vetorDeComandos1);

    std::cout << "\n--- Teste 2 ---" << std::endl;
    // Exemplo sem o "E" (processa até o fim)
    std::string qrCodeData2 = "10,20,30,40";
    std::vector<std::string> vetorDeComandos2 = splitString(qrCodeData2);
    processarComandos(vetorDeComandos2);

    return 0;
}
