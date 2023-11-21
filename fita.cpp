#include "fita.hpp"

// Implementação do construtor
Fita::Fita(const std::string& _titulo, int _codigo, int _quantidade, bool _rebobinada)
    : Filme(_titulo, _codigo, _quantidade), rebobinada(_rebobinada) {}

// Implementação dos métodos específicos para Fitas
bool Fita::estaRebobinada() const {
    return rebobinada;
}

void Fita::rebobinar() {
    rebobinada = true;
}

// Implementação do método virtual da classe base
double Fita::calcularValorLocacao(int dias) const {
    double valorLocacao = 5.0 * dias; // Preço fixo para Fitas
    if (!rebobinada) {
        valorLocacao += 2.0; // Adiciona a multa por não rebobinar
    }
    return valorLocacao;
}
