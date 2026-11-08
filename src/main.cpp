/**
 * @file main.cpp
 * @brief Ponto de entrada do Cine PDS: cria o cinema e executa o laço principal.
 */

#include <exception>
#include <iostream>

#include "Cinema.h"

using namespace std;

int main() {
    try {
        Cinema cinema;
        cinema.executar();
    } catch (const exception& erro) {
        cerr << "Erro inesperado: " << erro.what() << '\n';
        return 1;
    }
    return 0;
}
