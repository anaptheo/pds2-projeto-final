#include "filme.hpp"

// Implementação do construtor
Filme::Filme(const std::string& _titulo, int _codigo, int _quantidade)
    : titulo(_titulo), codigo(_codigo), quantidade(_quantidade), unidadesDisponiveis(0) {
    
}

// Implementação do destrutor
Filme::~Filme() {
    
}

// Implementação dos métodos de acesso
const std::string& Filme::getTitulo() const {
    return titulo;
}

int Filme::getCodigo() const {
    return codigo;
}

int Filme::getUnidadesDisponiveis() const {
    return unidadesDisponiveis;
}

// Implementação dos métodos específicos da classe

void Filme::incrementarUnidades() {
  unidadesDisponiveis++;
}

void Filme::decrementarUnidades(){
  unidadesDisponiveis--;
}
