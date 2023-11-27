#include "filme.hpp"

Filme::Filme(const std::string& titulo, int codigo, int quantidade, Tipo tipo)
    : titulo(titulo), codigo(codigo), quantidade(quantidade), tipo(tipo), unidadesDisponiveis(quantidade) {
}

Filme::~Filme() {
}

const std::string& Filme::getTitulo() const {
    return titulo;
}

int Filme::getCodigo() const {
    return codigo;
}

int Filme::getUnidadesDisponiveis() const {
    return unidadesDisponiveis;
}

int Filme::getQuantidade() const {
    return quantidade;
}

Filme::Tipo Filme::getTipo() const {
    return tipo;
}

void Filme::incrementarUnidades() {
    unidadesDisponiveis++;
}

void Filme::decrementarUnidades() {
    unidadesDisponiveis--;
}
