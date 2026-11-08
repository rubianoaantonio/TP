#include "Administrador.h"

#include <iostream>
#include <stdexcept>

#include "Cinema.h"
#include "Data.h"
#include "Entrada.h"
#include "Horario.h"

namespace {

const int kOpcaoSair = 0;
const int kOpcaoLancar = 1;
const int kOpcaoExcluir = 2;
const int kOpcaoListar = 3;

const int kDuracaoMaximaMinutos = 600;
const int kMaximoDiasEmCartaz = 365;
const int kMaximoHorariosPorDia = 10;

}  // namespace

Administrador::Administrador(const std::string& login, const std::string& senha)
    : Usuario(login, senha) {}

void Administrador::exibirMenu(Cinema& cinema) {
    while (true) {
        std::cout << "\n=== Administrador ===\n"
                  << kOpcaoLancar << ". Lançar filme\n"
                  << kOpcaoExcluir << ". Excluir filme\n"
                  << kOpcaoListar << ". Ver filmes em cartaz\n"
                  << kOpcaoSair << ". Sair\n";
        int opcao = Entrada::lerInteiro("Opção: ", kOpcaoSair, kOpcaoListar);
        if (opcao == kOpcaoSair)
            return;
        try {
            executarOpcao(opcao, cinema);
        } catch (const std::logic_error& erro) {
            std::cout << "Erro: " << erro.what() << '\n';
        }
    }
}

void Administrador::executarOpcao(int opcao, Cinema& cinema) {
    switch (opcao) {
        case kOpcaoLancar:
            lancarFilme(cinema);
            break;
        case kOpcaoExcluir:
            excluirFilme(cinema);
            break;
        case kOpcaoListar:
            cinema.listarFilmes();
            break;
    }
}

void Administrador::lancarFilme(Cinema& cinema) {
    std::string nome = Entrada::lerTexto("Nome do filme: ");
    int duracao = Entrada::lerInteiro("Duração (minutos): ", 1, kDuracaoMaximaMinutos);
    int sala = Entrada::lerInteiro("Sala (1 a 3): ", 1, Cinema::kQuantidadeSalas);
    std::cout << "Data de estreia\n";
    Data estreia = lerData();
    int dias = Entrada::lerInteiro("Dias em cartaz: ", 1, kMaximoDiasEmCartaz);
    std::vector<Horario> horarios = lerHorarios();

    cinema.lancarFilme(nome, duracao, sala, estreia, dias, horarios);
    std::cout << "Filme lançado com " << dias * static_cast<int>(horarios.size())
              << " sessão(ões).\n";
}

void Administrador::excluirFilme(Cinema& cinema) {
    int numeroFilmes = static_cast<int>(cinema.getFilmes().size());
    if (numeroFilmes == 0) {
        std::cout << "Nenhum filme em cartaz.\n";
        return;
    }
    cinema.listarFilmes();
    int escolha = Entrada::lerInteiro("Filme a excluir (0 para voltar): ", 0, numeroFilmes);
    if (escolha == 0)
        return;
    cinema.excluirFilme(escolha - 1);
    std::cout << "Filme excluído.\n";
}

Data Administrador::lerData() {
    int dia = Entrada::lerInteiro("  Dia: ", 1, 31);
    int mes = Entrada::lerInteiro("  Mês: ", 1, 12);
    int ano = Entrada::lerInteiro("  Ano (4 dígitos): ", 2000, 2100);
    return Data(dia, mes, ano);  // lança exceção se a data não existir (ex.: 31/02)
}

std::vector<Horario> Administrador::lerHorarios() {
    int quantidade = Entrada::lerInteiro("Quantos horários por dia: ", 1, kMaximoHorariosPorDia);
    std::vector<Horario> horarios;
    for (int i = 1; i <= quantidade; i++) {
        std::cout << "Horário " << i << '\n';
        int hora = Entrada::lerInteiro("  Hora (0 a 23): ", 0, 23);
        int minuto = Entrada::lerInteiro("  Minuto (0 a 59): ", 0, 59);
        horarios.push_back(Horario(hora, minuto));
    }
    return horarios;
}
