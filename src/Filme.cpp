#include "Filme.h"

#include <algorithm>
#include <stdexcept>

#include "Sala.h"
#include "Sessao.h"

Filme::Filme(const std::string& nome, int duracaoMinutos, Sala* sala)
    : nome_(nome), duracaoMinutos_(duracaoMinutos), sala_(sala) {
    if (nome.empty())
        throw std::invalid_argument("O nome do filme não pode ser vazio.");
    if (duracaoMinutos <= 0)
        throw std::invalid_argument("A duração deve ser maior que zero.");
    if (sala == nullptr)
        throw std::invalid_argument("Filme precisa de uma sala.");
}

Filme::~Filme() {
    liberarSessoes();
}

const std::string& Filme::getNome() const { return nome_; }
int Filme::getDuracao() const { return duracaoMinutos_; }
Sala* Filme::getSala() const { return sala_; }

void Filme::criarSessoes(const Data& estreia, int diasEmCartaz,
                         const std::vector<Horario>& horarios) {
    if (diasEmCartaz <= 0)
        throw std::invalid_argument("O filme precisa ficar ao menos 1 dia em cartaz.");
    if (horarios.empty())
        throw std::invalid_argument("Informe ao menos um horário.");

    for (int i = 0; i < diasEmCartaz; i++) {
        Data dia = estreia.somarDias(i);
        for (const Horario& horario : horarios) {
            if (sala_->temConflito(dia, horario, duracaoMinutos_)) {
                liberarSessoes();  // desfaz as sessões já criadas
                throw std::invalid_argument("Conflito na sala " +
                                            std::to_string(sala_->getNumero()) + " em " +
                                            dia.toString() + " às " + horario.toString() + ".");
            }
            Sessao* sessao = new Sessao(this, dia, horario, sala_);
            sessoes_.push_back(sessao);
            sala_->registrarSessao(sessao);
        }
    }
}

std::vector<Data> Filme::listarDias() const {
    std::vector<Data> dias;
    for (const Sessao* sessao : sessoes_)
        if (std::find(dias.begin(), dias.end(), sessao->getData()) == dias.end())
            dias.push_back(sessao->getData());
    std::sort(dias.begin(), dias.end());
    return dias;
}

std::vector<Horario> Filme::listarHorarios(const Data& dia) const {
    std::vector<Horario> horarios;
    for (const Sessao* sessao : sessoes_)
        if (sessao->getData() == dia)
            horarios.push_back(sessao->getHorario());
    std::sort(horarios.begin(), horarios.end());
    return horarios;
}

Sessao* Filme::buscarSessao(const Data& dia, const Horario& horario) const {
    for (Sessao* sessao : sessoes_)
        if (sessao->getData() == dia && sessao->getHorario() == horario)
            return sessao;
    throw std::invalid_argument("Sessão não encontrada em " + dia.toString() +
                                " às " + horario.toString() + ".");
}

bool Filme::temIngressosVendidos() const {
    for (const Sessao* sessao : sessoes_)
        if (sessao->temAssentosOcupados())
            return true;
    return false;
}

void Filme::liberarSessoes() {
    for (Sessao* sessao : sessoes_) {
        sala_->removerSessao(sessao);
        delete sessao;
    }
    sessoes_.clear();
}
