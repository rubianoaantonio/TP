/**
 * @file main.cpp
 * @brief Ponto de entrada do Cine PDS: cria o cinema e executa o laço principal.
 */

#include <exception>
#include <iostream>

#include "Cinema.h"

int main() {
    try {
        Cinema cinema;
        cinema.executar();
    } catch (const std::exception& erro) {
        std::cerr << "Erro inesperado: " << erro.what() << '\n';
        return 1;
    }
    return 0;
}
