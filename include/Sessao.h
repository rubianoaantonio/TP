#ifndef SESSAO_H
#define SESSAO_H

#include <string>
#include <vector>

#include "Data.h"
#include "Horario.h"

class Filme;
class Sala;

/**
 * @brief Exibição de um filme em uma sala, numa data e horário.
 *
 * Mantém o mapa 5x5 de assentos (fileiras A a E, assentos 1 a 5).
 * Códigos de assento têm o formato letra + número, por exemplo "B3".
 */
class Sessao {
public:
    /** @brief Quantidade de fileiras (A a E). */
    static const int kFileiras = 5;
    /** @brief Quantidade de assentos por fileira (1 a 5). */
    static const int kAssentosPorFileira = 5;

private:
    const Filme* filme_;
    Sala* sala_;
    Data data_;
    Horario horario_;
    bool ocupados_[kFileiras][kAssentosPorFileira];

public:
    /**
     * @brief Cria uma sessão com todos os assentos livres.
     * @param filme Filme exibido (não pode ser nulo).
     * @param data Data da sessão.
     * @param horario Horário de início.
     * @param sala Sala da sessão (não pode ser nula).
     * @throws std::invalid_argument se filme ou sala forem nulos.
     */
    Sessao(const Filme* filme, const Data& data, const Horario& horario, Sala* sala);

    /** @brief Retorna o filme exibido. */
    const Filme* getFilme() const;
    /** @brief Retorna a sala da sessão. */
    Sala* getSala() const;
    /** @brief Retorna a data da sessão. */
    const Data& getData() const;
    /** @brief Retorna o horário de início. */
    const Horario& getHorario() const;

    /**
     * @brief Calcula o horário de término (início + duração do filme).
     *
     * Após a meia-noite, retorna apenas o horário (ex.: 01:30), sem a data.
     * @return Horário de término.
     */
    Horario calcularTermino() const;

    /** @brief Exibe o mapa de assentos, distinguindo livres (.) de ocupados (X). */
    void exibirMapa() const;

    /**
     * @brief Reserva um ou mais assentos em uma única operação.
     *
     * Valida todos os códigos antes de reservar: se algum for inválido,
     * repetido ou já ocupado, nenhum assento é reservado.
     * @param codigos Códigos dos assentos (ex.: {"A1", "A2"}).
     * @throws std::invalid_argument se a lista estiver vazia ou algum código
     *         for inexistente, repetido ou já ocupado.
     */
    void reservarAssentos(const std::vector<std::string>& codigos);

    /**
     * @brief Libera um assento, que volta a ficar disponível.
     * @param codigo Código do assento (ex.: "B3").
     * @throws std::invalid_argument se o código for inexistente.
     */
    void liberarAssento(const std::string& codigo);

    /**
     * @brief Indica se um assento está ocupado.
     * @param codigo Código do assento.
     * @return true se estiver ocupado.
     * @throws std::invalid_argument se o código for inexistente.
     */
    bool estaOcupado(const std::string& codigo) const;

    /** @brief Indica se há pelo menos um assento ocupado (ingresso vendido). */
    bool temAssentosOcupados() const;

    /**
     * @brief Indica se um código de assento existe no mapa 5x5.
     * @param codigo Código a validar (aceita letra minúscula).
     * @return true se for de A1 a E5.
     */
    static bool ehCodigoValido(const std::string& codigo);

private:
    static void converterCodigo(const std::string& codigo, int& fileira, int& coluna);
};

#endif
