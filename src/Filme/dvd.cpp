/**
 * @file dvd.cpp
 * @brief Implementação dos métodos da classe DVD, uma classe filha da classe Filme.
 */

#include "dvd.hpp"

/**
 * @brief Construtor da classe DVD.
 * 
 * @param _titulo Título do DVD.
 * @param _codigo Código único do DVD.
 * @param _unidadesDisponiveis Quantidade de unidades disponíveis do DVD.
 * @param _categoria Categoria do DVD (Lançamento, Estoque ou Promoção).
 */

DVD::DVD(const std::string& _titulo, std::string _codigo, int _unidadesDisponiveis, Categoria _categoria)
    : Filme(_titulo, _codigo, Filme::Tipo::DVD, _unidadesDisponiveis), categoria(_categoria) {
}

/**
 * @brief Calcula o valor de locação do DVD, considerando a categoria e a quantidade de dias.
 * 
 * @param dias O número de dias para locação.
 * @return O valor total da locação do DVD.
 */

double DVD::calcularValorLocacao(int dias) const {
    double valorLocacao = 0.0;

    // Calcula o valor de locação baseado na categoria do DVD
    switch (categoria) {
        case Categoria::Lancamento:
            valorLocacao = 20.0 * dias;
            break;
        case Categoria::Estoque:
            valorLocacao = 10.0 * dias;
            break;
        case Categoria::Promocao:
            valorLocacao = 10.0; 
            break;
    }

    return valorLocacao;
}
