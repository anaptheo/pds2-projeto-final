/**
 * @file filme.cpp
 * @brief Implementação dos métodos da classe Filme, uma classe mãe para os diferentes tipos de filmes.
 */

#include "filme.hpp"

/**
 * @brief Construtor da classe Filme.
 * 
 * @param titulo Título do filme.
 * @param codigo Código único do filme.
 * @param tipo Tipo do filme (DVD, BluRay, etc.).
 * @param unidadesDisponiveis Quantidade de unidades disponíveis do filme.
 */

Filme::Filme(const std::string& titulo, std::string codigo, Filme::Tipo tipo, int unidadesDisponiveis)
    : titulo(titulo), codigo(codigo), tipo(tipo), unidadesDisponiveis(unidadesDisponiveis) {
    // Inicializa unidadesDisponiveis com 1
}

/**
 * @brief Destrutor da classe Filme.
 */

Filme::~Filme() {
}

/**
 * @brief Obtém o título do filme.
 * 
 * @return O título do filme.
 */

const std::string& Filme::getTitulo() const {
    return titulo;
}

/**
 * @brief Obtém o código único do filme.
 * 
 * @return O código único do filme.
 */

std::string Filme::getCodigo() const {
    return codigo;
}

/**
 * @brief Obtém a quantidade de unidades disponíveis do filme.
 * 
 * @return A quantidade de unidades disponíveis do filme.
 */

int Filme::getUnidadesDisponiveis() const {
    return unidadesDisponiveis;
}

/**
 * @brief Obtém o tipo do filme.
 * 
 * @return O tipo do filme (DVD, BluRay, etc.).
 */

Filme::Tipo Filme::getTipo() const {
    return tipo;
}

/**
 * @brief Adiciona unidades disponíveis ao filme.
 * 
 * @param quantidade A quantidade de unidades a serem adicionadas.
 */

void Filme::adicionarUnidadesDisponiveis(int quantidade) {
    unidadesDisponiveis += quantidade;
}

/**
 * @brief Remove uma unidade disponível do filme.
 */

void Filme::removerUnidadeDisponivel() {
    unidadesDisponiveis -= 1;
}

/**
 * @brief Calcula o valor de locação do filme, considerando a quantidade de dias.
 * 
 * @param dias Número de dias para locação.
 * @return Valor total da locação do filme.
 */
double Filme::calcularValorLocacao(int dias) const {
    // Implementação padrão, deve ser sobrescrito nas classes derivadas
    return 0.0;
}
