#include "Sala.h"

#include <algorithm>
#include <stdexcept>

#include "Filme.h"
#include "Sessao.h"

using namespace std;

namespace {

const int kMinutosPorDia = 24 * 60;

// Verdadeiro se o momento A (data e horário) vem antes do momento B.
bool vemAntes(const Data& dataA, const Horario& horaA, const Data& dataB, const Horario& horaB) {
    if (dataA != dataB)
        return dataA < dataB;
    return horaA < horaB;
}

// Data em que algo termina: se passar da meia-noite, avança os dias necessários.
Data calcularDataFim(const Data& data, const Horario& inicio, int minutos) {
    int diasExtras = (inicio.emMinutos() + minutos) / kMinutosPorDia;
    return data.somarDias(diasExtras);
}

}  // namespace

const int Sala::kIntervaloEntreSessoes;

Sala::Sala(int numero) : numero_(numero) {
    if (numero < 1)
        throw invalid_argument("Número de sala inválido.");
}

int Sala::getNumero() const {
    return numero_;
}

bool Sala::temConflito(const Data& data, const Horario& inicio, int duracaoMinutos) const {
    int ocupacaoNova = duracaoMinutos + kIntervaloEntreSessoes;
    Data dataFimNova = calcularDataFim(data, inicio, ocupacaoNova);
    Horario horaFimNova = inicio.somarMinutos(ocupacaoNova);

    for (const Sessao* sessao : sessoes_) {
        int ocupacao = sessao->getFilme()->getDuracao() + kIntervaloEntreSessoes;
        Data dataFim = calcularDataFim(sessao->getData(), sessao->getHorario(), ocupacao);
        Horario horaFim = sessao->getHorario().somarMinutos(ocupacao);

        bool novaComecaAntesDoFim = vemAntes(data, inicio, dataFim, horaFim);
        bool existenteComecaAntesDoFimDaNova =
            vemAntes(sessao->getData(), sessao->getHorario(), dataFimNova, horaFimNova);
        if (novaComecaAntesDoFim && existenteComecaAntesDoFimDaNova)
            return true;
    }
    return false;
}

void Sala::registrarSessao(Sessao* sessao) {
    if (sessao == nullptr)
        throw invalid_argument("Sessão nula.");
    sessoes_.push_back(sessao);
}

void Sala::removerSessao(Sessao* sessao) {
    sessoes_.erase(remove(sessoes_.begin(), sessoes_.end(), sessao), sessoes_.end());
}
