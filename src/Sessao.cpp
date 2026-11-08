#include "Sessao.h"

#include <cctype>
#include <iostream>
#include <stdexcept>

#include "Filme.h"
#include "Sala.h"

namespace {

const char kPrimeiraFileira = 'A';
const char kSimboloLivre = '.';
const char kSimboloOcupado = 'X';

}  // namespace

const int Sessao::kFileiras;
const int Sessao::kAssentosPorFileira;

Sessao::Sessao(const Filme* filme, const Data& data, const Horario& horario, Sala* sala)
    : filme_(filme), sala_(sala), data_(data), horario_(horario) {
    if (filme == nullptr || sala == nullptr)
        throw std::invalid_argument("Sessão precisa de filme e sala.");
    for (int fileira = 0; fileira < kFileiras; fileira++)
        for (int coluna = 0; coluna < kAssentosPorFileira; coluna++)
            ocupados_[fileira][coluna] = false;
}

const Filme* Sessao::getFilme() const { return filme_; }
Sala* Sessao::getSala() const { return sala_; }
const Data& Sessao::getData() const { return data_; }
const Horario& Sessao::getHorario() const { return horario_; }

Horario Sessao::calcularTermino() const {
    return horario_.somarMinutos(filme_->getDuracao());
}

void Sessao::exibirMapa() const {
    std::cout << "\n    ";
    for (int coluna = 1; coluna <= kAssentosPorFileira; coluna++)
        std::cout << coluna << ' ';
    std::cout << '\n';

    for (int fileira = 0; fileira < kFileiras; fileira++) {
        std::cout << static_cast<char>(kPrimeiraFileira + fileira) << "   ";
        for (int coluna = 0; coluna < kAssentosPorFileira; coluna++)
            std::cout << (ocupados_[fileira][coluna] ? kSimboloOcupado : kSimboloLivre) << ' ';
        std::cout << '\n';
    }
    std::cout << "Legenda: " << kSimboloLivre << " livre   " << kSimboloOcupado << " ocupado\n";
}

void Sessao::reservarAssentos(const std::vector<std::string>& codigos) {
    if (codigos.empty())
        throw std::invalid_argument("Nenhum assento informado.");

    bool escolhidos[kFileiras][kAssentosPorFileira] = {};
    for (const std::string& codigo : codigos) {
        int fileira = 0;
        int coluna = 0;
        converterCodigo(codigo, fileira, coluna);
        if (ocupados_[fileira][coluna])
            throw std::invalid_argument("Assento já reservado: " + codigo);
        if (escolhidos[fileira][coluna])
            throw std::invalid_argument("Assento repetido: " + codigo);
        escolhidos[fileira][coluna] = true;
    }

    for (int fileira = 0; fileira < kFileiras; fileira++)
        for (int coluna = 0; coluna < kAssentosPorFileira; coluna++)
            if (escolhidos[fileira][coluna])
                ocupados_[fileira][coluna] = true;
}

void Sessao::liberarAssento(const std::string& codigo) {
    int fileira = 0;
    int coluna = 0;
    converterCodigo(codigo, fileira, coluna);
    ocupados_[fileira][coluna] = false;
}

bool Sessao::estaOcupado(const std::string& codigo) const {
    int fileira = 0;
    int coluna = 0;
    converterCodigo(codigo, fileira, coluna);
    return ocupados_[fileira][coluna];
}

bool Sessao::temAssentosOcupados() const {
    for (int fileira = 0; fileira < kFileiras; fileira++)
        for (int coluna = 0; coluna < kAssentosPorFileira; coluna++)
            if (ocupados_[fileira][coluna])
                return true;
    return false;
}

bool Sessao::ehCodigoValido(const std::string& codigo) {
    if (codigo.size() != 2)
        return false;
    char letra = static_cast<char>(std::toupper(static_cast<unsigned char>(codigo[0])));
    int fileira = letra - kPrimeiraFileira;
    int coluna = codigo[1] - '1';
    return fileira >= 0 && fileira < kFileiras && coluna >= 0 && coluna < kAssentosPorFileira;
}

void Sessao::converterCodigo(const std::string& codigo, int& fileira, int& coluna) {
    if (!ehCodigoValido(codigo))
        throw std::invalid_argument("Assento inexistente: " + codigo);
    char letra = static_cast<char>(std::toupper(static_cast<unsigned char>(codigo[0])));
    fileira = letra - kPrimeiraFileira;
    coluna = codigo[1] - '1';
}
