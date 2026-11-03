#ifndef DATA_H
#define DATA_H

#include <string>

/**
 * @brief Representa uma data do calendário (dia, mês e ano).
 *
 * Objetos Data são sempre válidos: o construtor lança exceção
 * se a data não existir.
 */
class Data {
private:
    int dia_;
    int mes_;
    int ano_;

public:
    /**
     * @brief Cria uma data validada.
     * @param dia Dia do mês (1 a 31, conforme o mês).
     * @param mes Mês (1 a 12).
     * @param ano Ano com 4 dígitos (ex.: 2026).
     * @throws std::invalid_argument se a data não existir.
     */
    Data(int dia, int mes, int ano);

    /** @brief Retorna o dia. */
    int getDia() const;
    /** @brief Retorna o mês. */
    int getMes() const;
    /** @brief Retorna o ano com 4 dígitos. */
    int getAno() const;

    /**
     * @brief Retorna uma nova data n dias depois desta.
     * @param n Quantidade de dias (n >= 0).
     * @return A data resultante.
     * @throws std::invalid_argument se n for negativo.
     */
    Data somarDias(int n) const;

    /**
     * @brief Converte a data em dias desde 01/01/2000.
     *
     * Permite comparar e somar datas como números inteiros,
     * por exemplo para checar conflito entre sessões que
     * atravessam a meia-noite.
     * @return Quantidade de dias desde 01/01/2000 (01/01/2000 retorna 0).
     */
    int emDias() const;

    /**
     * @brief Formata a data como texto.
     * @return Texto no formato DD/MM/AA (ex.: 05/11/26).
     */
    std::string toString() const;

    /** @brief Verdadeiro se as duas datas são iguais. */
    bool operator==(const Data& outra) const;
    /** @brief Verdadeiro se as datas são diferentes. */
    bool operator!=(const Data& outra) const;
    /** @brief Verdadeiro se esta data vem antes da outra. */
    bool operator<(const Data& outra) const;
    /** @brief Verdadeiro se esta data vem antes ou é igual à outra. */
    bool operator<=(const Data& outra) const;
    /** @brief Verdadeiro se esta data vem depois da outra. */
    bool operator>(const Data& outra) const;
    /** @brief Verdadeiro se esta data vem depois ou é igual à outra. */
    bool operator>=(const Data& outra) const;

    /**
     * @brief Indica se o ano é bissexto.
     * @param ano Ano com 4 dígitos.
     * @return true se for bissexto.
     */
    static bool ehBissexto(int ano);

    /**
     * @brief Quantidade de dias de um mês.
     * @param mes Mês (1 a 12).
     * @param ano Ano, usado para fevereiro.
     * @return Número de dias do mês.
     */
    static int diasNoMes(int mes, int ano);

    /**
     * @brief Indica se dia, mês e ano formam uma data existente.
     * @param dia Dia do mês.
     * @param mes Mês.
     * @param ano Ano com 4 dígitos.
     * @return true se a data for válida.
     */
    static bool ehValida(int dia, int mes, int ano);
};

#endif