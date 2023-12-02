#ifndef FITA_HPP
#define FITA_HPP

#include "filme.hpp"

/**
 * @file fita.hpp
 * @brief Declaração da classe Fita, seus métodos e atributos.
 * @details Este arquivo define a classe Fita, que representa um filme no formato de fita.
 *          A classe herda da classe Filme e adiciona funcionalidades específicas às fitas,
 *          como rebobinamento e cálculo de valor de locação.
 * @class Fita
 * @details A classe Fita contém atributos como título, código, quantidade de unidades disponíveis,
 *          informações sobre se a fita está rebobinada e métodos para manipulação desses atributos.
 * @param rebobinada Indica se a fita está rebobinada (true) ou não (false).
 */

class Fita : public Filme {
private:
    bool rebobinada; /**< Indica se a fita está rebobinada (true) ou não (false). */

public:
    /**
     * @brief Construtor da classe Fita.
     * @param titulo Título do filme.
     * @param codigo Código único do filme.
     * @param quantidade Número de unidades disponíveis para locação.
     * @param _rebobinada Indica se a fita está rebobinada (true) ou não (false).
     */
    Fita(const std::string& titulo, std::string codigo, int quantidade, bool _rebobinada);

    /**
     * @brief Verifica se a fita está rebobinada.
     * @return True se a fita estiver rebobinada, false caso contrário.
     */
    bool estaRebobinada() const;

    /**
     * @brief Rebobina a fita.
     */
    void rebobinar();

    /**
     * @brief Calcula o valor total da locação da fita.
     * @param dias Número de dias pelos quais o filme será alugado.
     * @return O valor total da locação.
     */
    double calcularValorLocacao(int dias) const override;
};

#endif // FITA_HPP
