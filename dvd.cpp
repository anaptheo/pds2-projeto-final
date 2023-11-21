#include "dvd.hpp"

DVD::DVD(const std::string& _titulo, int _codigo, int _quantidade, Tipo _tipo)
    : Filme(_titulo, _codigo, _quantidade), tipo(_tipo) {}

double DVD::calcularValorLocacao(int dias) const {
    double valorLocacao = 0.0;

    switch (tipo) {
        case Tipo::Lancamento:
            valorLocacao = 20.0 * dias;
            break;
        case Tipo::Estoque:
            valorLocacao = 10.0 * dias;
            break;
        case Tipo::Promocao:
            valorLocacao = 10.0; 
            break;
    }

    return valorLocacao;
}
