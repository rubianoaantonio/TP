#ifndef ENTRADA_H
#define ENTRADA_H

#include <string>

/**
 * @brief Funções de leitura do teclado usadas por todos os menus.
 *
 * Concentram o tratamento de entrada inválida (RNF05): texto onde se
 * espera número e opções fora do intervalo são recusados e a pergunta
 * é refeita, sem encerrar o programa. Também limpam a tela e pausam
 * entre uma interação e outra, para o terminal não acumular texto.
 */
namespace Entrada {

/**
 * @brief Lê uma linha inteira digitada pelo usuário.
 * @param mensagem Texto exibido antes da leitura.
 * @return A linha digitada, sem espaços nas pontas.
 * @throws std::runtime_error se a entrada terminar (fim de arquivo).
 */
std::string lerTexto(const std::string& mensagem);

/**
 * @brief Lê um número inteiro dentro de um intervalo.
 *
 * Repete a pergunta até o usuário digitar um número válido.
 * @param mensagem Texto exibido antes da leitura.
 * @param minimo Menor valor aceito.
 * @param maximo Maior valor aceito.
 * @return O número digitado.
 * @throws std::runtime_error se a entrada terminar (fim de arquivo).
 */
int lerInteiro(const std::string& mensagem, int minimo, int maximo);

/**
 * @brief Limpa o terminal antes de exibir um menu.
 *
 * Usa o comando "cls" no Windows e um código de escape ANSI no
 * Linux e no macOS.
 */
void limparTela();

/**
 * @brief Espera o usuário apertar Enter, para que ele leia o resultado
 *        da operação antes de a tela ser limpa.
 * @throws std::runtime_error se a entrada terminar (fim de arquivo).
 */
void pausar();

}  // namespace Entrada

#endif
