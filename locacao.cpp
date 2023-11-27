/*#include "locacao.hpp"
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
*/

#include "locacao.hpp"
#include "filme.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

void Locacao::emiteReciboAluguel(Cliente* cliente) {
    std::cout << "Cliente " << cliente->getCpf() << " " << cliente->getNome() << " alugou os filmes:" << std::endl; 
    for (auto filme : cliente->getFilmesAlugados()) {
        std::cout << filme->getCodigo() << " " << filme->getTitulo() << " " << filme->getTipo() << std::endl;
    }
}

void Locacao::emiteReciboDevolucao(Cliente* cliente, int dias) {
    std::cout << "Cliente " << cliente->getCpf() << " " << cliente->getNome() << " devolveu os filmes:" << std::endl; 
    
    int valor_total = 0;
    for (auto filme : cliente->getFilmesAlugados()) {
        int valor_pagamento = filme->calcularValorLocacao(dias);
        std::cout << filme->getCodigo() << " " << valor_pagamento << std::endl;
        valor_total += valor_pagamento;
    }

    std::cout << "Total a pagar: " << valor_total << std::endl;
}

void Locacao::devolverFilme(Cliente* cliente, std::vector<Filme*> filmes, int dias) {
    const std::string cpfCliente = cliente->getCpf();
    auto it = std::find_if(_clientes_cadastrados.begin(), _clientes_cadastrados.end(), [cpfCliente](Cliente* c) 
    { return c->getCpf() == cpfCliente; });

    if (it != _clientes_cadastrados.end()) {
        emiteReciboDevolucao(cliente, dias);
    } else {
        std::cout << "Erro: CPF inexistente." << std::endl;
    }
}

void Locacao::alugarFilme(Cliente* cliente, std::vector<Filme*> filmes, int dias) {
    const std::string cpfCliente = cliente->getCpf();
    auto it = std::find_if(_clientes_cadastrados.begin(), _clientes_cadastrados.end(), [cpfCliente](Cliente* c) 
    { return c->getCpf() == cpfCliente; });

    if (it != _clientes_cadastrados.end()) {
        for (Filme* filme : filmes) {
            if (filme->getUnidadesDisponiveis()) {
                filme->decrementarUnidades();
                cliente->adicionarFilmeAlugado(filme); 
            } else {
                std::cout << "Filme código " << filme->getCodigo() << " inexistente" << std::endl;
            }
        }
        emiteReciboAluguel(cliente);
    } else {
        std::cout << "Erro: CPF inexistente." << std::endl;
    }
}

void Locacao::cadastrarFilme(Filme* filme) {
    _catalogo_filmes.push_back(filme);
}

void Locacao::removerFilme(int codigo) {
    auto it = std::remove_if(_catalogo_filmes.begin(), _catalogo_filmes.end(),
                             [codigo](Filme* filme) { return filme->getCodigo() == codigo; });

    if (it != _catalogo_filmes.end()) {
        _catalogo_filmes.erase(it, _catalogo_filmes.end());
    } else {
        std::cout << "Erro: Filme não encontrado." << std::endl;
    }
}

void Locacao::listarFilmes() {
    std::sort(_catalogo_filmes.begin(), _catalogo_filmes.end(), [](Filme* a, Filme* b) {
        return a->getCodigo() < b->getCodigo();
    });

    for (Filme* filme : _catalogo_filmes) {
        std::cout << "Código: " << filme->getCodigo() << " - Título: " << filme->getTitulo()
                  << " - Quantidade: " << filme->getUnidadesDisponiveis() << " - Tipo: " << filme->getTipo() << std::endl;
    }
}

void Locacao::cadastrarCliente(const std::string& nome, const std::string& cpf) {
    _clientes_cadastrados.push_back(new Cliente(nome, cpf));
}

void Locacao::removerCliente(const std::string& cpf) {
    auto it = std::remove_if(_clientes_cadastrados.begin(), _clientes_cadastrados.end(),
                             [cpf](Cliente* cliente) { return cliente->getCpf() == cpf; });

    if (it != _clientes_cadastrados.end()) {
        _clientes_cadastrados.erase(it, _clientes_cadastrados.end());
    } else {
        std::cout << "Erro: Cliente não encontrado." << std::endl;
    }
}

void Locacao::listarClientes() {
    for (Cliente* cliente : _clientes_cadastrados) {
        cliente->MostrarInfo();
    }
}

Filme* Locacao::getFilme(int codigo_filme) {
    for (auto filme : _catalogo_filmes) {
        if (filme->getCodigo() == codigo_filme) {
            return filme;
        }
    }
    return nullptr;
}