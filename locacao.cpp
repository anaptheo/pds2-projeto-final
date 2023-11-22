#include "locacao.hpp"
#include "filme.hpp"

#include <iostream>
#include <vector>

void Locacao::emiteReciboAluguel(Cliente* cliente) {
    cout << "Cliente" << cliente->getCpf() << " " << cliente->getNome() << " alugou os filmes:" << endl; 
    for (auto filme: cliente->getFilmesAlugados()) {
        cout << filme->getCodigo() << " " << filme->getTitulo() << " " << endl; //falta implementar o getTipo() (dvd/fita/bluray);
    }
}

void Locacao::emiteReciboDevolucao(Cliente* cliente, int dias) {
    cout << "Cliente" << cliente->getCpf() << " " << cliente->getNome() << " devolveu os filmes:" << endl; 
    
    int valor_total = 0;
    for (auto filme: cliente->getFilmesAlugados() ) {
        int valor_pagamento = filme->calcularValorLocacao(dias);
        cout << filme->getCodigo() << " " << valor_pagamento << endl;
        valor_total = valor_total + valor_pagamento;
    }

    cout << "Total a pagar: " << valor_total << endl;
}

void Locacao::devolverFilme(Cliente* cliente) {
    // adicionar ao unidadesDisponiveis de novo do vector this->catalogo_filmes ((usar o getFilme()))
    // tirar o filme do vector de _filmes_alugados de cliente
    // chamar a funcao de emitir recibo;
}

void Locacao::alugarFilme(Cliente* cliente, vector<Filme*> filmes) {
    // removr do unidadesDisponiveis do vector this->catalogo_filmes 
    // adicionar o filme ao vector de _filmes_alugados de cliente
    // chamar a funcao de emitir recibo;
}

void Locacao::ImprimirFilmes() {

}

Filme* Locacao::getFilme(int codigo_filme) {
    for (auto filme : _catalogo_filmes) {
        if (filme->getCodigo() == codigo_filme) {
            return filme;
        }
    }
}