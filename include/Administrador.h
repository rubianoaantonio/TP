#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <string>
#include <vector>

#include "Usuario.h"

class Data;
class Horario;

/**
 * @brief Administrador do cinema, criado na inicialização do sistema.
 *
 * Lê os dados no menu e encaminha lançamento e exclusão de filmes
 * para o Cinema, que faz as validações.
 */
class Administrador : public Usuario {
public:
    /**
     * @brief Cria o administrador.
     * @param login Login (não pode ser vazio).
     * @param senha Senha (não pode ser vazia).
     * @throws std::invalid_argument se login ou senha forem vazios.
     */
    Administrador(const std::string& login, const std::string& senha);

    /**
     * @brief Exibe o menu de administração até o administrador sair.
     * @param cinema Cinema cuja programação será alterada.
     */
    void exibirMenu(Cinema& cinema) override;

private:
    void executarOpcao(int opcao, Cinema& cinema);
    void lancarFilme(Cinema& cinema);
    void excluirFilme(Cinema& cinema);
    static Data lerData();
    static std::vector<Horario> lerHorarios();
};

#endif
