#include "Horario.h"

#include <stdexcept>

using namespace std;

namespace {

const int kMinutosPorHora = 60;
const int kMinutosPorDia = 24 * kMinutosPorHora;
const int kHoraMaxima = 23;
const int kMinutoMaximo = 59;

// Escreve o número com 2 dígitos, colocando um zero na frente se precisar (5 vira "05").
string doisDigitos(int numero) {
    if (numero < 10)
        return "0" + to_string(numero);
    return to_string(numero);
}

} 

Horario::Horario(int hora, int minuto) : hora_(hora), minuto_(minuto) {
    if (!ehValido(hora, minuto))
        throw invalid_argument("Horario fora do intervalo: " +
                                    to_string(hora) + ":" +
                                    to_string(minuto));
}

int Horario::getHora() const { return hora_; }
int Horario::getMinuto() const { return minuto_; }

int Horario::emMinutos() const {
    return hora_ * kMinutosPorHora + minuto_;
}

Horario Horario::somarMinutos(int m) const {
    if (m < 0)
        throw invalid_argument("Quantidade de minutos negativa.");

    int total = (emMinutos() + m) % kMinutosPorDia;
    return Horario(total / kMinutosPorHora, total % kMinutosPorHora);
}

string Horario::toString() const {
    return doisDigitos(hora_) + ":" + doisDigitos(minuto_);
}

bool Horario::operator==(const Horario& outro) const {
    return emMinutos() == outro.emMinutos();
}

bool Horario::operator<(const Horario& outro) const {
    return emMinutos() < outro.emMinutos();
}

bool Horario::operator!=(const Horario& outro) const { return !(*this == outro); }
bool Horario::operator>(const Horario& outro) const { return outro < *this; }
bool Horario::operator<=(const Horario& outro) const { return !(outro < *this); }
bool Horario::operator>=(const Horario& outro) const { return !(*this < outro); }

bool Horario::ehValido(int hora, int minuto) {
    return hora >= 0 && hora <= kHoraMaxima &&
           minuto >= 0 && minuto <= kMinutoMaximo;
}