#include "dvd.hpp"

DVD::DVD(const std::string& _titulo, std::string _codigo, int _unidadesDisponiveis, Categoria _categoria)
    : Filme(_titulo, _codigo, Filme::Tipo::DVD, _unidadesDisponiveis), categoria(_categoria) {
}

double DVD::calcularValorLocacao(int dias) const {
    double valorLocacao = 0.0;

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