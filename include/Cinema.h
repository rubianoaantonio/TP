#ifndef CINEMA_H
#define CINEMA_H

#include <string>
#include <vector>

#include "Data.h"
#include "Horario.h"

class Administrador;
class Cliente;
class Filme;
class Sala;
class Usuario;

/**
 * @brief Classe central do sistema: usuários, salas e cartaz de filmes.
 *
 * Cria o administrador e as 3 salas na inicialização, executa o laço
 * principal e libera toda a memória alocada no destrutor.
 */
class Cinema {
public:
    /** @brief Quantidade de salas do cinema (RNF08). */
    static const int kQuantidadeSalas = 3;

private:
    Administrador* administrador_;
    std::vector<Cliente*> clientes_;
    std::vector<Sala*> salas_;
    std::vector<Filme*> filmes_;

public:
    /** @brief Cria o administrador e as salas 1, 2 e 3. */
    Cinema();

    /** @brief Libera clientes, administrador, filmes e salas. */
    ~Cinema();

    /** @brief Cópia proibida: o cinema é dono de vários ponteiros. */
    Cinema(const Cinema&) = delete;
    /** @brief Atribuição proibida pelo mesmo motivo da cópia. */
    Cinema& operator=(const Cinema&) = delete;

    /** @brief Executa o menu inicial (entrar, cadastrar, sair) até o usuário sair. */
    void executar();

    /**
     * @brief Cadastra um novo cliente.
     * @param login Login desejado.
     * @param senha Senha desejada.
     * @throws std::invalid_argument se o login já existir ou se login/senha forem vazios.
     */
    void cadastrarCliente(const std::string& login, const std::string& senha);

    /**
     * @brief Autentica um usuário (cliente ou administrador).
     * @param login Login digitado.
     * @param senha Senha digitada.
     * @return O usuário autenticado.
     * @throws std::invalid_argument se o login não existir ou a senha estiver incorreta.
     */
    Usuario* autenticar(const std::string& login, const std::string& senha) const;

    /**
     * @brief Lança um filme, criando uma sessão por dia e horário.
     * @param nome Nome do filme.
     * @param duracaoMinutos Duração em minutos.
     * @param numeroSala Número da sala (1 a 3).
     * @param estreia Data de estreia.
     * @param diasEmCartaz Quantidade de dias em cartaz.
     * @param horarios Horários de exibição em cada dia.
     * @throws std::invalid_argument se a sala não existir, houver conflito
     *         de horário ou algum dado for inválido.
     */
    void lancarFilme(const std::string& nome, int duracaoMinutos, int numeroSala,
                     const Data& estreia, int diasEmCartaz, const std::vector<Horario>& horarios);

    /**
     * @brief Exclui um filme do cartaz.
     * @param indice Posição do filme no cartaz (começando em 0).
     * @throws std::out_of_range se o índice não existir.
     * @throws std::logic_error se o filme tiver ingressos vendidos.
     */
    void excluirFilme(int indice);

    /** @brief Retorna os filmes em cartaz. */
    const std::vector<Filme*>& getFilmes() const;

    /** @brief Exibe os filmes em cartaz, numerados, com duração e sala. */
    void listarFilmes() const;

    /**
     * @brief Busca uma sala pelo número.
     * @param numero Número da sala.
     * @return A sala encontrada.
     * @throws std::invalid_argument se a sala não existir.
     */
    Sala* buscarSala(int numero) const;

private:
    void executarOpcao(int opcao);
    void entrar();
    void cadastrarPeloMenu();
    bool loginExiste(const std::string& login) const;
};

#endif
