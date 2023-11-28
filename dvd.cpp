#include "dvd.hpp"

DVD::DVD(const std::string& titulo, int codigo, int quantidade, Categoria _categoria)
    : Filme(titulo, codigo, quantidade, Filme::Tipo::DVD), categoria(_categoria) {
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