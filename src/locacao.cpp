#include "locacao.hpp"
#include "dvd.hpp"
#include "bluray.hpp"
#include "fita.hpp"
#include <algorithm>
#include <iostream>

//getters para retornar filme/cliente por codigo/cpf

Filme* Locacao::getFilme(std::string codigo_filme) {
    for (auto filme : _catalogo_filmes) {
        if (filme->getCodigo() == codigo_filme) {
            return filme;
        }
    }
    return nullptr;
}

Cliente* Locacao::getCliente(const std::string& cpf) {
    auto it = std::find_if(_clientes_cadastrados.begin(), _clientes_cadastrados.end(),
                            [cpf](Cliente* cliente) { return cliente->getCpf() == cpf; });

    return (it != _clientes_cadastrados.end()) ? *it : nullptr;
}

//impressao dos recibos

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
    
    if (cliente->getPontos() == 1) {
        std::cout << "PARABÉNS! Você já acumulou 5 pontos de fidelidade, então ganhou um desconto de R$ 10,00 no seu aluguel de hoje. Aproveite!" << std::endl;
        
        cliente->zerarPontos();
        valor_total -= 10;
    }
    std::cout << "Total a pagar: " << valor_total << std::endl;
}

//métodos para alugar e devolver filmes


void Locacao::alugarFilmes(const std::string& cpf, std::vector<Filme*>& filmes) {
    Cliente* cliente = getCliente(cpf);

    for (Filme* filme : filmes) {
        if (filme->getUnidadesDisponiveis() > 0 ) {
            cliente->adicionarFilmeAlugado(filme);
            filme->removerUnidadeDisponivel();
        } else {
            throw std::out_of_range("Todos os filmes desse tipo estão alugados.");
        }
    }

    emiteReciboAluguel(cliente);

    // Ajuste para o total de pontos de fidelidade do cliente
    int totalPontos = 0;
    for (Filme* filme : filmes) {
        totalPontos++; // Adiciona pontos por cada unidade alugada
    }

    cliente->adicionarPontos(totalPontos);

    std::cout << "Total de pontos de fidelidade adquiridos nessa operação: " << totalPontos << std::endl; 
    std::cout << "Total de pontos de fidelidade acumulados: " << cliente->getPontos() << std::endl; 

    // Limpar o vetor após o aluguel
    filmes.clear();
}


void Locacao::devolverFilmes(Cliente* cliente, int dias) {
    emiteReciboDevolucao(cliente, dias);
    cliente->devolverFilmesAlugados();
}

//métodos para cadastrar ou remover filmes do catálogo

void Locacao::cadastrarFilme(Filme* filme) {
    // Verifica se já existe um filme com o mesmo código
    auto it = std::find_if(_catalogo_filmes.begin(), _catalogo_filmes.end(),
                           [filme](Filme* f) { return f->getCodigo() == filme->getCodigo(); });

    if (it != _catalogo_filmes.end()) {
        // Filme com o mesmo código encontrado, adicione a quantidade disponível
        (*it)->adicionarUnidadesDisponiveis(filme->getUnidadesDisponiveis());
        delete filme; // Não precisamos mais do filme, podemos liberar a memória
    } else {
        // Nenhum filme com o mesmo código encontrado, adiciona o novo filme ao catálogo
        _catalogo_filmes.push_back(filme);
    }
}


void Locacao::removerFilme(std::string codigo) {
    auto it = std::remove_if(_catalogo_filmes.begin(), _catalogo_filmes.end(),
                             [codigo](Filme* filme) { return filme->getCodigo() == codigo; });

    if (it != _catalogo_filmes.end()) {
        _catalogo_filmes.erase(it, _catalogo_filmes.end());
        // Limpa a memória alocada para o filme removido
        for (auto filme : _catalogo_filmes) {
            if (filme->getCodigo() == codigo) {
                delete filme;
                break; // Não precisamos continuar procurando
            }
        }
    } else {
        throw std::invalid_argument("ERRO: Filme não encontrado.");
    }
}


//métodos para cadastrar ou remover clientes

void Locacao::cadastrarCliente(const std::string& nome, const std::string& cpf) {
    _clientes_cadastrados.push_back(new Cliente(nome, cpf));
    std::cout << "Cliente cadastrado com sucesso!" << std::endl;
}

void Locacao::removerCliente(const std::string& cpf) {
    auto it = std::remove_if(_clientes_cadastrados.begin(), _clientes_cadastrados.end(),
                             [cpf](Cliente* cliente) { return cliente->getCpf() == cpf; });

    if (it != _clientes_cadastrados.end()) {
        _clientes_cadastrados.erase(it, _clientes_cadastrados.end());
    } else {
        throw std::invalid_argument("ERRO: Cliente não encontrado.");
    }
}

//métodos para listar filmes e clientes

void Locacao::listarFilmesCodigo() {

    // Ordena os filmes por código
    std::sort(_catalogo_filmes.begin(), _catalogo_filmes.end(), [](Filme* a, Filme* b) {
        return a->getCodigo() < b->getCodigo();
    });

    // Exibe os filmes
    for (Filme* filme : _catalogo_filmes) {
        std::cout << "Codigo: " << filme->getCodigo() << " - Titulo: " << filme->getTitulo()
                  << " - Quantidade: " << filme->getUnidadesDisponiveis() << " - Tipo: " << filme->getTipo() << std::endl;
    }
}

void Locacao::listarFilmesTitulo() {

    // Ordena os filmes por título
    std::sort(_catalogo_filmes.begin(), _catalogo_filmes.end(), [](Filme* a, Filme* b) {

        if (a->getTitulo().compare(b->getTitulo()) < 0 ){
            return true;
        }else if (a->getTitulo().compare(b->getTitulo()) > 0 ){
            return false;
        }else if (a->getTitulo().compare(b->getTitulo()) == 0 ){
            return true;
        }
    });

    // Exibe os filmes
    for (Filme* filme : _catalogo_filmes) {
        std::cout << "Codigo: " << filme->getCodigo() << " - Titulo: " << filme->getTitulo()
                  << " - Quantidade: " << filme->getUnidadesDisponiveis() << " - Tipo: " << filme->getTipo() << std::endl;
    }

}

void Locacao::listarClientesCodigo() {
    std::sort(_clientes_cadastrados.begin(), _clientes_cadastrados.end(), [](Cliente* a, Cliente* b) {
        long long int cpf_a = std::stoll(a->getCpf());
        long long int cpf_b = std::stoll(b->getCpf());
        return cpf_a < cpf_b;
    });
    for (Cliente* cliente : _clientes_cadastrados) {
        cliente->mostrarInfo();
    }
}

void Locacao::listarClientesNome(){
    std::sort(_clientes_cadastrados.begin(), _clientes_cadastrados.end(), [](Cliente* a, Cliente* b) {
        if (a->getNome().compare(b->getNome()) < 0 ){
            return true;
        }else if (a->getNome().compare(b->getNome()) > 0 ){
            return false;
        }else if (a->getNome().compare(b->getNome()) == 0 ){
            return true;
        }
    });
    for (Cliente* cliente : _clientes_cadastrados) {
        cliente->mostrarInfo();
    }
}

