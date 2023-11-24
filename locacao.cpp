#include "locacao.hpp"
#include "filme.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

void Locacao::emiteReciboAluguel(Cliente* cliente) {
    cout << "Cliente" << cliente->getCpf() << " " << cliente->getNome() << " alugou os filmes:" << endl; 
    for (auto filme: cliente->getFilmesAlugados()) {
        cout << filme->getCodigo() << " " << filme->getTitulo() << " " << filme->getTipo() << endl; //falta implementar o getTipo() (dvd/fita/bluray);
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

void Locacao::devolverFilme(Cliente* cliente, vector<Filme*> filmes, int dias) {

    const string cpfCliente = cliente->getCpf();  //verificar se o CPF do cliente também é valido.
    auto it = find_if(_clientes_cadastrados.begin(), _clientes_cadastrados.end(), [cpfCliente](Cliente* c) 
    { return c->getCpf() == cpfCliente; });
    if (it != _clientes_cadastrados.end()) { //se achou cliente
        emiteReciboDevolucao(cliente, dias);
    }
    //verificar o cpf do cliente
    //imprimir o cpf e nome devolveu os filmes
    //codigo e valor do filme
    //emitir recibo
    else{
        cout << "Erro: CPF inexistente." << endl;
    }
    // adicionar ao unidadesDisponiveis de novo do vector this->catalogo_filmes ((usar o getFilme()))
    // tirar o filme do vector de _filmes_alugados de cliente
    // chamar a funcao de emitir recibo;
}

void Locacao::alugarFilme(Cliente* cliente, vector<Filme*> filmes, int dias) {
   
    const string cpfCliente = cliente->getCpf();  //verificar se o CPF do cliente também é valido.
    auto it = find_if(_clientes_cadastrados.begin(), _clientes_cadastrados.end(), [cpfCliente](Cliente* c) 
    { return c->getCpf() == cpfCliente; });
    if (it != _clientes_cadastrados.end()) {
        (*it)->MostrarInfo();
        // Cliente encontrado, pode prosseguir com a locação
        
    //for para ver se o filme está disponível
        for (Filme* filme : filmes) { 
                if (filme->getUnidadesDisponiveis()) {
                    filme->decrementarUnidades();
                    cliente->adicionarFilmeAlugado(filme); 

                } else {
                    cout << "Filme código " << filme->getCodigo() << "inexistente";
                }
            }
        emiteReciboAluguel(cliente);
   
    }else{
        cout << "Erro: CPF inexistente." << endl;
    }
}

void Locacao::ImprimirFilmes() {
    // Ordena o vetor _catalogo_filmes com base nos códigos dos filmes
    sort(_catalogo_filmes.begin(), _catalogo_filmes.end(), [](Filme* a, Filme* b) {
        return a->getCodigo() < b->getCodigo();
    });
    // Imprime os filmes ordenados
    for (Filme* filme : _catalogo_filmes) {
        cout << "Código: " << filme->getCodigo() << " - Título: " << filme->getTitulo() << " - Quantidade" << 
        filme->getUnidadesDisponiveis() <<  " - Tipo: " << filme->getTipo() << endl;
    }

}

Filme* Locacao::getFilme(int codigo_filme) {
    for (auto filme : _catalogo_filmes) {
        if (filme->getCodigo() == codigo_filme) {
            return filme;
        }
    }
}