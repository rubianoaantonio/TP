#include "Cinema.h"

#include <iostream>
#include <stdexcept>

#include "Administrador.h"
#include "Cliente.h"
#include "Entrada.h"
#include "Filme.h"
#include "Sala.h"

namespace {

const char* const kLoginAdministrador = "admin";
const char* const kSenhaAdministrador = "admin123";

const int kOpcaoSair = 0;
const int kOpcaoEntrar = 1;
const int kOpcaoCadastrar = 2;

}  // namespace

const int Cinema::kQuantidadeSalas;

Cinema::Cinema() : administrador_(nullptr) {
    administrador_ = new Administrador(kLoginAdministrador, kSenhaAdministrador);
    for (int numero = 1; numero <= kQuantidadeSalas; numero++)
        salas_.push_back(new Sala(numero));
}

Cinema::~Cinema() {
    for (Cliente* cliente : clientes_)
        delete cliente;
    delete administrador_;
    for (Filme* filme : filmes_)  // filmes antes das salas: o Filme avisa a Sala ao ser destruído
        delete filme;
    for (Sala* sala : salas_)
        delete sala;
}

void Cinema::executar() {
    try {
        while (true) {
            std::cout << "\n=== Cine PDS ===\n"
                      << kOpcaoEntrar << ". Entrar\n"
                      << kOpcaoCadastrar << ". Criar conta\n"
                      << kOpcaoSair << ". Sair\n";
            int opcao = Entrada::lerInteiro("Opção: ", kOpcaoSair, kOpcaoCadastrar);
            if (opcao == kOpcaoSair)
                break;
            executarOpcao(opcao);
        }
    } catch (const std::runtime_error&) {
        std::cout << "\nEntrada encerrada.\n";
    }
    std::cout << "Até logo!\n";
}

void Cinema::cadastrarCliente(const std::string& login, const std::string& senha) {
    if (loginExiste(login))
        throw std::invalid_argument("O login \"" + login + "\" já está em uso.");
    clientes_.push_back(new Cliente(login, senha));
}

Usuario* Cinema::autenticar(const std::string& login, const std::string& senha) const {
    Usuario* usuario = nullptr;
    if (administrador_->getLogin() == login)
        usuario = administrador_;
    for (Cliente* cliente : clientes_)
        if (cliente->getLogin() == login)
            usuario = cliente;

    if (usuario == nullptr)
        throw std::invalid_argument("Login não encontrado. Crie uma conta para continuar.");
    if (!usuario->verificarSenha(senha))
        throw std::invalid_argument("Senha incorreta.");
    return usuario;
}

void Cinema::lancarFilme(const std::string& nome, int duracaoMinutos, int numeroSala,
                         const Data& estreia, int diasEmCartaz,
                         const std::vector<Horario>& horarios) {
    Sala* sala = buscarSala(numeroSala);
    Filme* filme = new Filme(nome, duracaoMinutos, sala);
    try {
        filme->criarSessoes(estreia, diasEmCartaz, horarios);
    } catch (...) {
        delete filme;  // evita vazamento quando há conflito de horário
        throw;
    }
    filmes_.push_back(filme);
}

void Cinema::excluirFilme(int indice) {
    if (indice < 0 || indice >= static_cast<int>(filmes_.size()))
        throw std::out_of_range("Filme inexistente.");
    if (filmes_[indice]->temIngressosVendidos())
        throw std::logic_error("O filme tem ingressos vendidos e não pode ser excluído.");
    delete filmes_[indice];
    filmes_.erase(filmes_.begin() + indice);
}

const std::vector<Filme*>& Cinema::getFilmes() const {
    return filmes_;
}

void Cinema::listarFilmes() const {
    if (filmes_.empty()) {
        std::cout << "Nenhum filme em cartaz.\n";
        return;
    }
    for (size_t i = 0; i < filmes_.size(); i++)
        std::cout << i + 1 << ". " << filmes_[i]->getNome()
                  << " (" << filmes_[i]->getDuracao() << " min) - Sala "
                  << filmes_[i]->getSala()->getNumero() << '\n';
}

Sala* Cinema::buscarSala(int numero) const {
    for (Sala* sala : salas_)
        if (sala->getNumero() == numero)
            return sala;
    throw std::invalid_argument("Sala " + std::to_string(numero) + " não existe.");
}

void Cinema::executarOpcao(int opcao) {
    try {
        if (opcao == kOpcaoEntrar)
            entrar();
        else if (opcao == kOpcaoCadastrar)
            cadastrarPeloMenu();
    } catch (const std::logic_error& erro) {
        std::cout << "Erro: " << erro.what() << '\n';
    }
}

void Cinema::entrar() {
    std::string login = Entrada::lerTexto("Login: ");
    std::string senha = Entrada::lerTexto("Senha: ");
    Usuario* usuario = autenticar(login, senha);
    usuario->exibirMenu(*this);  // polimorfismo: menu de Cliente ou de Administrador
}

void Cinema::cadastrarPeloMenu() {
    std::string login = Entrada::lerTexto("Novo login: ");
    std::string senha = Entrada::lerTexto("Nova senha: ");
    cadastrarCliente(login, senha);
    std::cout << "Conta criada. Use a opção Entrar para acessar.\n";
}

bool Cinema::loginExiste(const std::string& login) const {
    if (administrador_->getLogin() == login)
        return true;
    for (const Cliente* cliente : clientes_)
        if (cliente->getLogin() == login)
            return true;
    return false;
}
