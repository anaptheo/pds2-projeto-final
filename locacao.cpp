#include "locacao.hpp"
#include <algorithm>
#include <iostream>

Cliente* Locacao::getCliente(const std::string& cpf) {
    auto it = std::find_if(_clientes_cadastrados.begin(), _clientes_cadastrados.end(),
                            [cpf](Cliente* cliente) { return cliente->getCpf() == cpf; });

    return (it != _clientes_cadastrados.end()) ? *it : nullptr;
}

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

void Locacao::devolverFilmes(const std::string& cpf, const std::vector<Filme*>& filmes) {
    Cliente* cliente = getCliente(cpf);

    if (cliente != nullptr) {
        if (!filmes.empty()) {
            for (Filme* filme : filmes) {
                cliente->devolverFilmeAlugado(filme);
            }
        } else {
            throw std::out_of_range("Erro: Lista de filmes vazia.");
        }
    } 
}

void Locacao::alugarFilmes(const std::string& cpf, std::vector<Filme*>& filmes, int dias) {
    Cliente* cliente = getCliente(cpf);

    if (cliente != nullptr) {
        for (Filme* filme : filmes) {
            cliente->adicionarFilmeAlugado(filme);
        }

        emiteReciboAluguel(cliente);

        // Ajuste para o total de pontos de fidelidade do cliente
        int totalPontos = 0;
        for (Filme* filme : filmes) {
            totalPontos += filme->getQuantidade(); // Adiciona pontos por cada unidade alugada
        }
        cliente->AdicionarPontos(totalPontos);

        std::cout << "Total de pontos de fidelidade acumulados: " << totalPontos << std::endl; //tem q ver se isso nao vai afetar a avaliação

        std::cout << "Total a pagar: ";
        double totalPagar = 0;
        for (Filme* filme : filmes) {
            totalPagar += filme->calcularValorLocacao(dias);
        }
        std::cout << totalPagar << std::endl;

        // Limpar o vetor após o aluguel
        filmes.clear();
    } else {
        throw std::invalid_argument("Erro: CPF inexistente.");
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
        throw std::invalid_argument("Erro: Filme não encontrado.");
    }
}

void Locacao::listarFilmes() {

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
        throw std::invalid_argument("Erro: Cliente não encontrado.");
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