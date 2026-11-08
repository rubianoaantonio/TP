#ifndef FILME_H
#define FILME_H

#include <string>
#include <vector>

#include "Data.h"
#include "Horario.h"

class Sala;
class Sessao;

/**
 * @brief Filme em cartaz, dono das suas sessões.
 *
 * Cria uma sessão para cada combinação de dia e horário e libera
 * todas elas no destrutor.
 */
class Filme {
private:
    std::string nome_;
    int duracaoMinutos_;
    Sala* sala_;
    std::vector<Sessao*> sessoes_;

public:
    /**
     * @brief Cria um filme ainda sem sessões.
     * @param nome Nome do filme (não pode ser vazio).
     * @param duracaoMinutos Duração em minutos (maior que zero).
     * @param sala Sala onde o filme será exibido (não pode ser nula).
     * @throws std::invalid_argument se algum parâmetro for inválido.
     */
    Filme(const std::string& nome, int duracaoMinutos, Sala* sala);

    /** @brief Libera todas as sessões e as remove da agenda da sala. */
    ~Filme();

    /** @brief Cópia proibida: o filme é dono de ponteiros para sessões. */
    Filme(const Filme&) = delete;
    /** @brief Atribuição proibida pelo mesmo motivo da cópia. */
    Filme& operator=(const Filme&) = delete;

    /** @brief Retorna o nome do filme. */
    const std::string& getNome() const;
    /** @brief Retorna a duração em minutos. */
    int getDuracao() const;
    /** @brief Retorna a sala do filme. */
    Sala* getSala() const;

    /**
     * @brief Cria uma sessão para cada combinação de dia e horário.
     *
     * Se alguma sessão entrar em conflito com a agenda da sala (inclusive
     * com outra sessão deste mesmo filme), nenhuma sessão é criada.
     * @param estreia Primeiro dia em cartaz.
     * @param diasEmCartaz Quantidade de dias (maior que zero).
     * @param horarios Horários de exibição em cada dia (não pode ser vazio).
     * @throws std::invalid_argument se houver conflito ou parâmetro inválido.
     */
    void criarSessoes(const Data& estreia, int diasEmCartaz, const std::vector<Horario>& horarios);

    /** @brief Lista, em ordem, os dias em que o filme tem sessão. */
    std::vector<Data> listarDias() const;

    /**
     * @brief Lista, em ordem, os horários de sessão de um dia.
     * @param dia Dia escolhido.
     * @return Horários do dia (vazio se não houver sessão).
     */
    std::vector<Horario> listarHorarios(const Data& dia) const;

    /**
     * @brief Busca a sessão de um dia e horário.
     * @param dia Dia da sessão.
     * @param horario Horário de início.
     * @return A sessão encontrada.
     * @throws std::invalid_argument se não existir sessão nesse dia e horário.
     */
    Sessao* buscarSessao(const Data& dia, const Horario& horario) const;

    /** @brief Indica se alguma sessão do filme tem ingresso vendido. */
    bool temIngressosVendidos() const;

private:
    void liberarSessoes();
};

#endif
