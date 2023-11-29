#include "bluray.hpp"
#include <string>

// Inicialização da variável estática
int Bluray::quantidadeAparelhos = 10; // Defina a quantidade inicial desejada

// Implementação do construtor
Bluray::Bluray(const std::string& _titulo, int _codigo, int _quantidade)
    : Filme(_titulo, _codigo, _quantidade, Filme::Tipo::BluRay), playerAlugado(false) {}

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
        playerAlugado = true;
    } else {
        throw std::invalid_argument("ERRO: todos os Blu-ray Players estão alugados no momento."); // chutei q era invalid argument sl
    }
}

void Bluray::devolverAparelho() {
    quantidadeAparelhos++;
    playerAlugado = false;
}

// Implementação do método virtual da classe base
double Bluray::calcularValorLocacao(int dias) const {
    // Valor fixo para locação de Blu-ray
    double valorLocacao = 25.0 * dias;

    // Verifica se foi alugado um player junto com o filme
    if (playerAlugado) {
        valorLocacao += 20.0; // Adiciona o valor fixo do aluguel do player
    }


    return valorLocacao;
}
