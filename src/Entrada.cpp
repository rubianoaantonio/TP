#include "Entrada.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace {

const char* const kEspacos = " \t\r\n";

std::string removerEspacosNasPontas(const std::string& texto) {
    size_t inicio = texto.find_first_not_of(kEspacos);
    if (inicio == std::string::npos)
        return "";
    size_t fim = texto.find_last_not_of(kEspacos);
    return texto.substr(inicio, fim - inicio + 1);
}

int converterParaInteiro(const std::string& texto) {
    size_t caracteresLidos = 0;
    int valor = std::stoi(texto, &caracteresLidos);  // lança se não for número
    if (caracteresLidos != texto.size())
        throw std::invalid_argument("Texto com caracteres extras.");
    return valor;
}

}  // namespace

std::string Entrada::lerTexto(const std::string& mensagem) {
    std::cout << mensagem;
    std::string linha;
    if (!std::getline(std::cin, linha))
        throw std::runtime_error("Entrada encerrada.");
    return removerEspacosNasPontas(linha);
}

int Entrada::lerInteiro(const std::string& mensagem, int minimo, int maximo) {
    while (true) {
        std::string texto = lerTexto(mensagem);
        try {
            int valor = converterParaInteiro(texto);
            if (valor >= minimo && valor <= maximo)
                return valor;
        } catch (const std::logic_error&) {
            // invalid_argument ou out_of_range: cai na mensagem abaixo
        }
        std::cout << "Valor inválido. Digite um número entre " << minimo
                  << " e " << maximo << ".\n";
    }
}

void Entrada::limparTela() {
#ifdef _WIN32
    std::system("cls");
#else
    std::cout << "\033[2J\033[H" << std::flush;  // apaga a tela e volta o cursor ao topo
#endif
}

void Entrada::pausar() {
    lerTexto("\nPressione Enter para continuar...");
}
