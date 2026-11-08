#include "Data.h"

#include <stdexcept>

using namespace std;

namespace {

const int kMesesPorAno = 12;
const int kDiasFevereiroBissexto = 29;
const int kAnoMinimo = 2000;
const int kAnoMaximo = 2100;
const int kDiasPorMes[kMesesPorAno + 1] =
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};  // índice 0 não usado

// Escreve o número com 2 dígitos, colocando um zero na frente se precisar (5 vira "05").
string doisDigitos(int numero) {
    if (numero < 10)
        return "0" + to_string(numero);
    return to_string(numero);
}

}  

Data::Data(int dia, int mes, int ano) : dia_(dia), mes_(mes), ano_(ano) {
    if (!ehValida(dia, mes, ano))
        throw invalid_argument("Data inexistente: " + to_string(dia) +
                                    "/" + to_string(mes) + "/" +
                                    to_string(ano));
}

int Data::getDia() const { return dia_; }
int Data::getMes() const { return mes_; }
int Data::getAno() const { return ano_; }

Data Data::somarDias(int n) const {
    if (n < 0)
        throw invalid_argument("Quantidade de dias negativa.");

    int dia = dia_;
    int mes = mes_;
    int ano = ano_;

    while (n > 0) {
        int diasRestantesNoMes = diasNoMes(mes, ano) - dia;
        if (n <= diasRestantesNoMes) {
            dia += n;
            n = 0;
        } else {
            n -= diasRestantesNoMes + 1;  // +1: salto para o dia 1 do mês seguinte
            dia = 1;
            mes++;
            if (mes > kMesesPorAno) {
                mes = 1;
                ano++;
            }
        }
    }
    return Data(dia, mes, ano);
}

string Data::toString() const {
    return doisDigitos(dia_) + "/" + doisDigitos(mes_) + "/" + doisDigitos(ano_ % 100);
}

bool Data::operator==(const Data& outra) const {
    return dia_ == outra.dia_ && mes_ == outra.mes_ && ano_ == outra.ano_;
}

bool Data::operator<(const Data& outra) const {
    if (ano_ != outra.ano_)
        return ano_ < outra.ano_;
    if (mes_ != outra.mes_)
        return mes_ < outra.mes_;
    return dia_ < outra.dia_;
}

bool Data::operator!=(const Data& outra) const { return !(*this == outra); }
bool Data::operator>(const Data& outra) const { return outra < *this; }
bool Data::operator<=(const Data& outra) const { return !(outra < *this); }
bool Data::operator>=(const Data& outra) const { return !(*this < outra); }

bool Data::ehBissexto(int ano) {
    return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
}

int Data::diasNoMes(int mes, int ano) {
    if (mes == 2 && ehBissexto(ano))
        return kDiasFevereiroBissexto;
    return kDiasPorMes[mes];
}

bool Data::ehValida(int dia, int mes, int ano) {
    if (ano < kAnoMinimo || ano > kAnoMaximo)
        return false;
    if (mes < 1 || mes > kMesesPorAno)
        return false;
    return dia >= 1 && dia <= diasNoMes(mes, ano);
}