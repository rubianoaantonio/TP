#include "Usuario.h"

#include <stdexcept>

Usuario::Usuario(const std::string& login, const std::string& senha)
    : login_(login), senha_(senha) {
    if (login.empty() || senha.empty())
        throw std::invalid_argument("Login e senha não podem ser vazios.");
}

Usuario::~Usuario() {}

const std::string& Usuario::getLogin() const {
    return login_;
}

bool Usuario::verificarSenha(const std::string& senha) const {
    return senha == senha_;
}
