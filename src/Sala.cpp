#include "Sala.h"

#include <algorithm>
#include <stdexcept>

#include "Sessao.h"

const int Sala::kIntervaloEntreSessoes;

Sala::Sala(int numero) : numero_(numero) {
    if (numero < 1)
        throw std::invalid_argument("Número de sala inválido.");
}

int Sala::getNumero() const {
    return numero_;
}

bool Sala::temConflito(const Data& data, const Horario& inicio, int duracaoMinutos) const {
    int novoInicio = Sessao::calcularMinutosAbsolutos(data, inicio);
    int novoFim = novoInicio + duracaoMinutos + kIntervaloEntreSessoes;

    for (const Sessao* sessao : sessoes_) {
        int inicioExistente = sessao->calcularInicioAbsoluto();
        int fimExistente = sessao->calcularFimAbsoluto() + kIntervaloEntreSessoes;
        if (novoInicio < fimExistente && inicioExistente < novoFim)
            return true;
    }
    return false;
}

void Sala::registrarSessao(Sessao* sessao) {
    if (sessao == nullptr)
        throw std::invalid_argument("Sessão nula.");
    sessoes_.push_back(sessao);
}

void Sala::removerSessao(Sessao* sessao) {
    sessoes_.erase(std::remove(sessoes_.begin(), sessoes_.end(), sessao), sessoes_.end());
}
