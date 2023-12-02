/**
 * @file bluray.cpp
 * @brief Implementação dos métodos da classe Bluray, uma classe filha da classe Filme.
 */

#include "bluray.hpp"
#include <stdexcept>

// Inicialização da variável estática
int Bluray::quantidadeAparelhos = 10; // Defina a quantidade inicial desejada

/**
 * @brief Construtor da classe Bluray.
 * 
 * @param _titulo Título do Blu-ray.
 * @param _codigo Código único do Blu-ray.
 * @param _unidadesDisponiveis Quantidade de unidades disponíveis do Blu-ray.
 */

Bluray::Bluray(const std::string& _titulo, std::string _codigo, int _unidadesDisponiveis)
    : Filme(_titulo, _codigo, Filme::Tipo::BluRay, _unidadesDisponiveis), playerAlugado(false) {}

/**
 * @brief Obtém a quantidade de aparelhos de Blu-ray disponíveis.
 * 
 * @return A quantidade de aparelhos de Blu-ray disponíveis.
 */

int Bluray::getQuantidadeAparelhosDisponiveis() {
    return quantidadeAparelhos;
}

/**
 * @brief Define a quantidade total de aparelhos de Blu-ray.
 * 
 * @param quantidade A nova quantidade total de aparelhos de Blu-ray.
 */

void Bluray::setQuantidadeAparelhos(int quantidade) {
    quantidadeAparelhos = quantidade;
}

/**
 * @brief Realiza o aluguel de um aparelho de Blu-ray, se disponível.
 * 
 * @throws std::invalid_argument Se todos os aparelhos de Blu-ray estiverem alugados.
 */

void Bluray::alugarAparelho() {
    if (quantidadeAparelhos > 0) {
        quantidadeAparelhos--;
        playerAlugado = true;
    } else {
        throw std::invalid_argument("ERRO: todos os Blu-ray Players estão alugados no momento.");
    }
}

/**
 * @brief Devolve um aparelho de Blu-ray.
 */

void Bluray::devolverAparelho() {
    quantidadeAparelhos++;
    playerAlugado = false;
}

/**
 * @brief Calcula o valor total da locação do Blu-ray.
 * 
 * @param dias Número de dias pelos quais o filme será alugado.
 * @return O valor total da locação.
 */

double Bluray::calcularValorLocacao(int dias) const {
    // Valor fixo para locação de Blu-ray
    double valorLocacao = 25.0 * dias;

    // Verifica se foi alugado um player junto com o filme
    if (playerAlugado) {
        valorLocacao += 20.0; // Adiciona o valor fixo do aluguel do player
    }

    return valorLocacao;
}
