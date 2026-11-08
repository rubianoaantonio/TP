#ifndef HORARIO_H
#define HORARIO_H

#include <string>

/**
 * @brief Representa um horário do dia (hora e minuto).
 *
 * Objetos Horario são sempre válidos: o construtor lança exceção
 * se a hora ou o minuto estiverem fora do intervalo.
 */
class Horario {
private:
    int hora_;
    int minuto_;

public:
    /**
     * @brief Cria um horário validado.
     * @param hora Hora (0 a 23).
     * @param minuto Minuto (0 a 59).
     * @throws std::invalid_argument se fora do intervalo.
     */
    Horario(int hora, int minuto);

    /** @brief Retorna a hora. */
    int getHora() const;
    /** @brief Retorna o minuto. */
    int getMinuto() const;

    /**
     * @brief Converte o horário em minutos desde 00:00.
     * @return Total de minutos (ex.: 14:30 retorna 870).
     */
    int emMinutos() const;

    /**
     * @brief Retorna um novo horário m minutos depois deste.
     *
     * Se passar de 23:59, o resultado volta a contar a partir de 00:00.
     * @param m Quantidade de minutos (m >= 0).
     * @return O horário resultante.
     * @throws std::invalid_argument se m for negativo.
     */
    Horario somarMinutos(int m) const;

    /**
     * @brief Formata o horário como texto.
     * @return Texto no formato HH:MM (ex.: 09:05).
     */
    std::string toString() const;

    /** @brief Verdadeiro se os dois horários são iguais. */
    bool operator==(const Horario& outro) const;
    /** @brief Verdadeiro se os horários são diferentes. */
    bool operator!=(const Horario& outro) const;
    /** @brief Verdadeiro se este horário vem antes do outro. */
    bool operator<(const Horario& outro) const;
    /** @brief Verdadeiro se este horário vem antes ou é igual ao outro. */
    bool operator<=(const Horario& outro) const;
    /** @brief Verdadeiro se este horário vem depois do outro. */
    bool operator>(const Horario& outro) const;
    /** @brief Verdadeiro se este horário vem depois ou é igual ao outro. */
    bool operator>=(const Horario& outro) const;

    /**
     * @brief Indica se hora e minuto estão no intervalo válido.
     * @param hora Hora a verificar.
     * @param minuto Minuto a verificar.
     * @return true se 0 <= hora <= 23 e 0 <= minuto <= 59.
     */
    static bool ehValido(int hora, int minuto);
};

#endif