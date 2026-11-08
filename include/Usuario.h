#ifndef USUARIO_H
#define USUARIO_H

#include <string>

class Cinema;

/**
 * @brief Classe abstrata para qualquer pessoa que entra no sistema.
 *
 * Guarda login e senha e declara o menu, que cada subclasse
 * (Cliente e Administrador) especializa.
 */
class Usuario {
private:
    std::string login_;
    std::string senha_;

public:
    /**
     * @brief Cria um usuário.
     * @param login Login (não pode ser vazio).
     * @param senha Senha (não pode ser vazia).
     * @throws std::invalid_argument se login ou senha forem vazios.
     */
    Usuario(const std::string& login, const std::string& senha);

    /** @brief Destrutor virtual, necessário para classes com herança. */
    virtual ~Usuario();

    /** @brief Retorna o login do usuário. */
    const std::string& getLogin() const;

    /**
     * @brief Verifica se a senha informada confere.
     * @param senha Senha digitada.
     * @return true se for igual à senha cadastrada.
     */
    bool verificarSenha(const std::string& senha) const;

    /**
     * @brief Exibe o menu do usuário até ele escolher sair.
     * @param cinema Cinema sobre o qual as operações são feitas.
     */
    virtual void exibirMenu(Cinema& cinema) = 0;
};

#endif
