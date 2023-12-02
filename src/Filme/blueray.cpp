#include "bluray.hpp"
#include <string>

// Inicialização da variável estática
int Bluray::quantidadeAparelhos = 10; // Defina a quantidade inicial desejada

// Implementação do construtor
Bluray::Bluray(const std::string& _titulo, std::string _codigo, int _unidadesDisponiveis)
    : Filme(_titulo, _codigo, Filme::Tipo::BluRay, _unidadesDisponiveis), playerAlugado(false) {}

// Implementação dos métodos específicos para Blu-rays
int Bluray::getQuantidadeAparelhosDisponiveis() {
    return quantidadeAparelhos;
}

void Bluray::setQuantidadeAparelhos(int quantidade) {
    quantidadeAparelhos = quantidade;
}

void Bluray::alugarAparelho() {
    if (quantidadeAparelhos > 0) {
        quantidadeAparelhos--;
    } else {
        throw std::invalid_argument("ERRO: todos os Blu-ray Players estão alugados no momento."); // chutei q era invalid argument sl
    }
}

void Bluray::devolverAparelho() {
    quantidadeAparelhos++;
}

// Implementação do método virtual da classe base
double Bluray::calcularValorLocacao(int dias) const {
    double valorLocacao = 25.0 * dias;
    return valorLocacao;
}

