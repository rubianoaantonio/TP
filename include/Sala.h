#ifndef SALA_H
#define SALA_H

#include <vector>

#include "Data.h"
#include "Horario.h"

class Sessao;

/**
 * @brief Sala de exibição do cinema.
 *
 * Mantém as sessões agendadas nela e detecta conflitos de horário.
 * A Sala não é dona das sessões: quem cria e destrói é o Filme.
 */
class Sala {
public:
    /** @brief Intervalo obrigatório entre duas sessões na mesma sala. */
    static const int kIntervaloEntreSessoes = 15;

private:
    int numero_;
    std::vector<Sessao*> sessoes_;

public:
    /**
     * @brief Cria uma sala.
     * @param numero Número que identifica a sala (maior que zero).
     * @throws std::invalid_argument se o número for menor que 1.
     */
    explicit Sala(int numero);

    /** @brief Retorna o número da sala. */
    int getNumero() const;

    /**
     * @brief Indica se uma nova sessão entraria em conflito com as já agendadas.
     *
     * Considera a duração do filme mais o intervalo de 15 minutos, inclusive
     * para sessões que atravessam a meia-noite.
     * @param data Data de início da nova sessão.
     * @param inicio Horário de início da nova sessão.
     * @param duracaoMinutos Duração do filme, em minutos.
     * @return true se houver sobreposição.
     */
    bool temConflito(const Data& data, const Horario& inicio, int duracaoMinutos) const;

    /**
     * @brief Registra uma sessão agendada nesta sala.
     * @param sessao Sessão a registrar (não pode ser nula).
     * @throws std::invalid_argument se a sessão for nula.
     */
    void registrarSessao(Sessao* sessao);

    /**
     * @brief Remove uma sessão da agenda (usado quando o filme sai de cartaz).
     * @param sessao Sessão a remover; se não estiver agendada, nada acontece.
     */
    void removerSessao(Sessao* sessao);
};

#endif
