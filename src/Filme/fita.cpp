/**
 * @file fita.cpp
 * @brief Implementação dos métodos da classe Fita, uma classe filha da classe Filme, representando uma fita de vídeo.
 */

#include "fita.hpp"

/**
 * @brief Construtor da classe Fita.
 * 
 * @param _titulo Título da fita.
 * @param _codigo Código único da fita.
 * @param _quantidade Quantidade de unidades disponíveis da fita.
 * @param _rebobinada Estado da rebobinação da fita.
 */

Fita::Fita(const std::string& _titulo, std::string _codigo, int _quantidade, bool _rebobinada)
    : Filme(_titulo, _codigo, Filme::Tipo::Fita, _quantidade), rebobinada(_rebobinada) {}


/**
 * @brief Verifica se a fita está rebobinada.
 * 
 * @return Verdadeiro se a fita estiver rebobinada, falso caso contrário.
 */

bool Fita::estaRebobinada() const {
    return rebobinada;
}

/**
 * @brief Rebobina a fita.
 */

void Fita::rebobinar() {
    rebobinada = true;
}

/**
 * @brief Calcula o valor de locação da fita com base na quantidade de dias e no estado de rebobinação.
 * 
 * @param dias Quantidade de dias para locação.
 * @return O valor total da locação da fita.
 */

double Fita::calcularValorLocacao(int dias) const {
    double valorLocacao = 5.0 * dias; // Preço fixo para Fitas
    if (!rebobinada) {
        valorLocacao += 2.0; // Adiciona a multa por não rebobinar
    }
    return valorLocacao;
}
