#include "Ingresso.h"

#include <iostream>
#include <stdexcept>

#include "Filme.h"
#include "Sala.h"
#include "Sessao.h"

Ingresso::Ingresso(Sessao* sessao, const std::string& assento)
    : sessao_(sessao), assento_(assento) {
    if (sessao == nullptr)
        throw std::invalid_argument("Ingresso precisa de uma sessão.");
}

Sessao* Ingresso::getSessao() const { return sessao_; }
const std::string& Ingresso::getAssento() const { return assento_; }

void Ingresso::exibir() const {
    std::cout << sessao_->getFilme()->getNome()
              << " | Sala " << sessao_->getSala()->getNumero()
              << " | " << sessao_->getData().toString()
              << " | " << sessao_->getHorario().toString()
              << " - " << sessao_->calcularTermino().toString()
              << " | Assento " << assento_ << '\n';
}

void Ingresso::cancelar() {
    sessao_->liberarAssento(assento_);
}
