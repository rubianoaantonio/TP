#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
#include <vector>

#include "Usuario.h"

class Filme;
class Ingresso;
class Sessao;

/**
 * @brief Cliente do cinema: compra, consulta e cancela ingressos.
 *
 * É dono dos seus ingressos e os libera no destrutor.
 */
class Cliente : public Usuario {
private:
    std::vector<Ingresso*> ingressos_;

public:
    /**
     * @brief Cria um cliente sem ingressos.
     * @param login Login (não pode ser vazio).
     * @param senha Senha (não pode ser vazia).
     * @throws std::invalid_argument se login ou senha forem vazios.
     */
    Cliente(const std::string& login, const std::string& senha);

    /** @brief Libera os ingressos do cliente. */
    ~Cliente() override;

    /** @brief Cópia proibida: o cliente é dono de ponteiros para ingressos. */
    Cliente(const Cliente&) = delete;
    /** @brief Atribuição proibida pelo mesmo motivo da cópia. */
    Cliente& operator=(const Cliente&) = delete;

    /**
     * @brief Exibe o menu do cliente até ele escolher sair.
     * @param cinema Cinema de onde vêm os filmes em cartaz.
     */
    void exibirMenu(Cinema& cinema) override;

    /**
     * @brief Adiciona um ingresso comprado; o cliente passa a ser o dono.
     * @param ingresso Ingresso alocado com new (não pode ser nulo).
     * @throws std::invalid_argument se o ingresso for nulo.
     */
    void adicionarIngresso(Ingresso* ingresso);

    /** @brief Exibe a aba "Meus Ingressos", numerada a partir de 1. */
    void listarIngressos() const;

    /**
     * @brief Cancela um ingresso e devolve o assento à sessão.
     * @param indice Posição do ingresso na lista (começando em 0).
     * @throws std::out_of_range se o índice não existir.
     */
    void cancelarIngresso(int indice);

    /**
     * @brief Indica se o cliente tem ingresso de uma sessão.
     * @param sessao Sessão a verificar.
     * @return true se algum ingresso for dessa sessão.
     */
    bool possuiIngressoDaSessao(const Sessao* sessao) const;

    /** @brief Retorna quantos ingressos o cliente possui. */
    int getQuantidadeIngressos() const;

private:
    void executarOpcao(int opcao, Cinema& cinema);
    void comprarIngressos(Cinema& cinema);
    Filme* escolherFilme(Cinema& cinema) const;
    Sessao* escolherSessao(const Filme& filme) const;
    void cancelarIngressoPeloMenu();
    static std::vector<std::string> separarCodigos(const std::string& linha);
};

#endif
