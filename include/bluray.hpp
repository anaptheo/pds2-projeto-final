#ifndef BLURAY_HPP
#define BLURAY_HPP

#include <iostream>
#include <string>

#include "filme.hpp"

/**
 * @file bluray.hpp
 * @brief Declaração da classe Bluray, seus métodos e atributos.
 * @details Este arquivo define a classe Bluray, que representa um filme no formato Blu-ray.
 *          A classe herda da classe Filme e adiciona funcionalidades específicas ao Blu-ray,
 *          como a gestão de aparelhos Blu-ray e cálculo de valor de locação.
 * @class Bluray
 * @details A classe Bluray contém atributos como título, código, quantidade de unidades disponíveis,
 *          quantidade de aparelhos Blu-ray e informações sobre o aluguel de aparelhos.
 * @param quantidadeAparelhos Quantidade de aparelhos Blu-ray disponíveis para aluguel.
 * @param playerAlugado Indica se um player Blu-ray foi alugado junto com o filme.
 */

class Bluray : public Filme {
private:
    static int quantidadeAparelhos; /**< Quantidade de aparelhos Blu-ray disponíveis para aluguel. Variável estática compartilhada entre todos os objetos Bluray. */
    bool playerAlugado; /**< Indica se um player Blu-ray foi alugado junto com o filme. */

public:
    /**
     * @brief Construtor da classe Bluray.
     * @param titulo Título do filme.
     * @param codigo Código único do filme.
     * @param unidadesDisponiveis Número de unidades disponíveis para locação.
     */
    Bluray(const std::string& titulo, std::string codigo, int unidadesDisponiveis);

    /**
     * @brief Obtém a quantidade de aparelhos Blu-ray disponíveis para locação.
     * @return A quantidade de aparelhos disponíveis.
     */
    static int getQuantidadeAparelhosDisponiveis();

    /**
     * @brief Define a quantidade de aparelhos Blu-ray disponíveis para locação.
     * @param quantidade Nova quantidade de aparelhos disponíveis.
     */
    static void setQuantidadeAparelhos(int quantidade);

    /**
     * @brief Realiza o aluguel de um aparelho Blu-ray junto com o filme.
     * @note A quantidade de aparelhos disponíveis será reduzida.
     * @throws std::invalid_argument Se não houver aparelhos disponíveis.
     */
    
    void alugarAparelho();

    /**
     * @brief Devolve o aparelho Blu-ray alugado.
     * @note A quantidade de aparelhos disponíveis será incrementada.
     */
    void devolverAparelho();

    /**
     * @brief Calcula o valor total da locação do Blu-ray.
     * @param dias Número de dias pelos quais o filme será alugado.
     * @return O valor total da locação.
     * @note Adiciona um custo fixo se um aparelho Blu-ray foi alugado.
     */
    double calcularValorLocacao(int dias) const override;
};

#endif // BLURAY_HPP
