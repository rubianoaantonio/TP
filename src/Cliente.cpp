#include "Cliente.h"

#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "Cinema.h"
#include "Entrada.h"
#include "Filme.h"
#include "Ingresso.h"
#include "Sessao.h"

namespace {

const int kOpcaoSair = 0;
const int kOpcaoVerFilmes = 1;
const int kOpcaoComprar = 2;
const int kOpcaoMeusIngressos = 3;
const int kOpcaoCancelar = 4;

}  // namespace

Cliente::Cliente(const std::string& login, const std::string& senha)
    : Usuario(login, senha) {}

Cliente::~Cliente() {
    for (Ingresso* ingresso : ingressos_)
        delete ingresso;
}

void Cliente::exibirMenu(Cinema& cinema) {
    while (true) {
        Entrada::limparTela();
        std::cout << "\n=== Cliente: " << getLogin() << " ===\n"
                  << kOpcaoVerFilmes << ". Ver filmes em cartaz\n"
                  << kOpcaoComprar << ". Comprar ingressos\n"
                  << kOpcaoMeusIngressos << ". Meus Ingressos\n"
                  << kOpcaoCancelar << ". Cancelar ingresso\n"
                  << kOpcaoSair << ". Sair\n";
        int opcao = Entrada::lerInteiro("Opção: ", kOpcaoSair, kOpcaoCancelar);
        if (opcao == kOpcaoSair)
            return;
        try {
            executarOpcao(opcao, cinema);
        } catch (const std::logic_error& erro) {
            std::cout << "Erro: " << erro.what() << '\n';
        }
        Entrada::pausar();  // deixa o resultado visível antes de limpar a tela
    }
}

void Cliente::adicionarIngresso(Ingresso* ingresso) {
    if (ingresso == nullptr)
        throw std::invalid_argument("Ingresso nulo.");
    ingressos_.push_back(ingresso);
}

void Cliente::listarIngressos() const {
    if (ingressos_.empty()) {
        std::cout << "Você ainda não tem ingressos.\n";
        return;
    }
    for (size_t i = 0; i < ingressos_.size(); i++) {
        std::cout << i + 1 << ". ";
        ingressos_[i]->exibir();
    }
}

void Cliente::cancelarIngresso(int indice) {
    if (indice < 0 || indice >= getQuantidadeIngressos())
        throw std::out_of_range("Ingresso inexistente.");
    ingressos_[indice]->cancelar();
    delete ingressos_[indice];
    ingressos_.erase(ingressos_.begin() + indice);
}

bool Cliente::possuiIngressoDaSessao(const Sessao* sessao) const {
    for (const Ingresso* ingresso : ingressos_)
        if (ingresso->getSessao() == sessao)
            return true;
    return false;
}

int Cliente::getQuantidadeIngressos() const {
    return static_cast<int>(ingressos_.size());
}

void Cliente::executarOpcao(int opcao, Cinema& cinema) {
    switch (opcao) {
        case kOpcaoVerFilmes:
            cinema.listarFilmes();
            break;
        case kOpcaoComprar:
            comprarIngressos(cinema);
            break;
        case kOpcaoMeusIngressos:
            listarIngressos();
            break;
        case kOpcaoCancelar:
            cancelarIngressoPeloMenu();
            break;
    }
}

void Cliente::comprarIngressos(Cinema& cinema) {
    Filme* filme = escolherFilme(cinema);
    if (filme == nullptr)
        return;
    Sessao* sessao = escolherSessao(*filme);
    if (sessao == nullptr)
        return;

    sessao->exibirMapa();
    std::string linha = Entrada::lerTexto("Assentos separados por espaço (ex.: A1 A2): ");
    std::vector<std::string> codigos = separarCodigos(linha);
    sessao->reservarAssentos(codigos);  // lança exceção se algum assento for inválido

    for (const std::string& codigo : codigos)
        adicionarIngresso(new Ingresso(sessao, codigo));
    std::cout << codigos.size() << " ingresso(s) comprado(s).\n";
}

Filme* Cliente::escolherFilme(Cinema& cinema) const {
    const std::vector<Filme*>& filmes = cinema.getFilmes();
    if (filmes.empty()) {
        std::cout << "Nenhum filme em cartaz.\n";
        return nullptr;
    }
    cinema.listarFilmes();
    int numeroFilmes = static_cast<int>(filmes.size());
    int escolha = Entrada::lerInteiro("Filme (0 para voltar): ", 0, numeroFilmes);
    return escolha == 0 ? nullptr : filmes[escolha - 1];
}

Sessao* Cliente::escolherSessao(const Filme& filme) const {
    std::vector<Data> dias = filme.listarDias();
    for (size_t i = 0; i < dias.size(); i++)
        std::cout << i + 1 << ". " << dias[i].toString() << '\n';
    int numeroDias = static_cast<int>(dias.size());
    int dia = Entrada::lerInteiro("Dia (0 para voltar): ", 0, numeroDias);
    if (dia == 0)
        return nullptr;

    std::vector<Horario> horarios = filme.listarHorarios(dias[dia - 1]);
    for (size_t i = 0; i < horarios.size(); i++)
        std::cout << i + 1 << ". " << horarios[i].toString() << '\n';
    int numeroHorarios = static_cast<int>(horarios.size());
    int horario = Entrada::lerInteiro("Horário (0 para voltar): ", 0, numeroHorarios);
    if (horario == 0)
        return nullptr;

    return filme.buscarSessao(dias[dia - 1], horarios[horario - 1]);
}

void Cliente::cancelarIngressoPeloMenu() {
    listarIngressos();
    if (ingressos_.empty())
        return;
    int escolha = Entrada::lerInteiro("Ingresso a cancelar (0 para voltar): ", 0,
                                      getQuantidadeIngressos());
    if (escolha == 0)
        return;
    cancelarIngresso(escolha - 1);
    std::cout << "Ingresso cancelado. O assento está livre novamente.\n";
}

std::vector<std::string> Cliente::separarCodigos(const std::string& linha) {
    std::vector<std::string> codigos;
    std::istringstream leitor(linha);
    std::string codigo;
    while (leitor >> codigo) {
        for (char& caractere : codigo)
            caractere = static_cast<char>(std::toupper(static_cast<unsigned char>(caractere)));
        codigos.push_back(codigo);
    }
    return codigos;
}
