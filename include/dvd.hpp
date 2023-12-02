#ifndef DVD_HPP
#define DVD_HPP

#include "filme.hpp"

/**
 * @file dvd.hpp
 * @brief Declaração da classe DVD, seus métodos e atributos.
 * @details Este arquivo define a classe DVD, que representa um filme no formato DVD.
 *          A classe herda da classe Filme e adiciona funcionalidades específicas ao DVD,
 *          como a definição da categoria e cálculo de valor de locação.
 * @class DVD
 * @details A classe DVD contém atributos como título, código, quantidade de unidades disponíveis
 *          e informações sobre a categoria do filme.
 * @param categoria Categoria do DVD (Lançamento, Estoque, Promoção).
 */

enum class Categoria {
    Lancamento, /**< Categoria de lançamento do DVD. */
    Estoque,    /**< Categoria de estoque do DVD. */
    Promocao    /**< Categoria de promoção do DVD. */
};

class DVD : public Filme {
protected:
    Categoria categoria; /**< Categoria do DVD (Lançamento, Estoque, Promoção). */

public:
    /**
     * @brief Construtor da classe DVD.
     * @param titulo Título do filme.
     * @param codigo Código único do filme.
     * @param unidadesDisponiveis Número de unidades disponíveis para locação.
     * @param _categoria Categoria do DVD (Lançamento, Estoque, Promoção).
     */
    DVD(const std::string& titulo, std::string codigo, int unidadesDisponiveis, Categoria _categoria);

    /**
     * @brief Calcula o valor total da locação do DVD.
     * @param dias Número de dias pelos quais o filme será alugado.
     * @return O valor total da locação.
     * @note Adiciona um custo fixo baseado na categoria do DVD.
     */
    double calcularValorLocacao(int dias) const override;
};

#endif // DVD_HPP
