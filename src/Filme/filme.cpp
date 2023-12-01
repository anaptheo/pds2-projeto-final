#include "filme.hpp"

Filme::Filme(const std::string& titulo, std::string codigo, Filme::Tipo tipo, int unidadesDisponiveis)
    : titulo(titulo), codigo(codigo), tipo(tipo), unidadesDisponiveis(unidadesDisponiveis) {
    // Inicializa unidadesDisponiveis com 1
}


Filme::~Filme() {
}

const std::string& Filme::getTitulo() const {
    return titulo;
}

std::string Filme::getCodigo() const {
    return codigo;
}

int Filme::getUnidadesDisponiveis() const {
    return unidadesDisponiveis;
}

Filme::Tipo Filme::getTipo() const {
    return tipo;
}

void Filme::adicionarUnidadesDisponiveis(int quantidade) {
    unidadesDisponiveis += quantidade;
}

void Filme::removerUnidadeDisponivel() {
    unidadesDisponiveis -= 1;
}
