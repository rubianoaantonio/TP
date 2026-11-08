#ifndef INGRESSO_H
#define INGRESSO_H

#include <string>

class Sessao;

/**
 * @brief Ingresso comprado por um cliente: uma sessão e um assento.
 */
class Ingresso {
private:
    Sessao* sessao_;
    std::string assento_;

public:
    /**
     * @brief Cria um ingresso para um assento já reservado na sessão.
     * @param sessao Sessão do ingresso (não pode ser nula).
     * @param assento Código do assento (ex.: "B3").
     * @throws std::invalid_argument se a sessão for nula.
     */
    Ingresso(Sessao* sessao, const std::string& assento);

    /** @brief Retorna a sessão do ingresso. */
    Sessao* getSessao() const;
    /** @brief Retorna o código do assento. */
    const std::string& getAssento() const;

    /** @brief Exibe filme, sala, data, horário (início e término) e assento. */
    void exibir() const;

    /** @brief Cancela o ingresso, devolvendo o assento à sessão. */
    void cancelar();
};

#endif
