#include "locacao.hpp"
#include "DVD.hpp"
#include "Bluray.hpp"
#include "Fita.hpp"
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

    std::cout << "Total a pagar: " << valor_total << std::endl;
}

//métodos para alugar e devolver filmes


void Locacao::alugarFilmes(const std::string& cpf, std::vector<Filme*>& filmes) {
    Cliente* cliente = getCliente(cpf);

    if (cliente != nullptr) {
        for (Filme* filme : filmes) {
            cliente->adicionarFilmeAlugado(filme);
        }

        emiteReciboAluguel(cliente);

        // Ajuste para o total de pontos de fidelidade do cliente
        int totalPontos = 0;
        for (Filme* filme : filmes) {
            totalPontos++; // Adiciona pontos por cada unidade alugada
        }
        cliente->AdicionarPontos(totalPontos);

        std::cout << "Total de pontos de fidelidade acumulados: " << totalPontos << std::endl; //tem q ver se isso nao vai afetar a avaliação

        // Limpar o vetor após o aluguel
        filmes.clear();
    } else {
        throw std::invalid_argument("Erro: CPF inexistente.");
    }
}

void Locacao::devolverFilmes(const std::string& cpf, int dias) {
    Cliente* cliente = getCliente(cpf);

    if (cliente != nullptr) {
        vector<Filme*>& filmes_alugados = cliente->getFilmesAlugados();
        
        double totalPagar = 0;
        for (Filme* filme : filmes_alugados) {
            double valorLocacao;

            // Verifica o tipo do filme
            if (filme->getTipo() == Filme::Tipo::DVD) {
                DVD* dvd = dynamic_cast<DVD*>(filme);
                if (dvd) {
                    // Calcula o valor de locação específico para DVD
                    valorLocacao = dvd->calcularValorLocacao(dias);
                }
            } else if (filme->getTipo() == Filme::Tipo::BluRay) {
                Bluray* bluray = dynamic_cast<Bluray*>(filme);
                if (bluray) {
                    // Calcula o valor de locação específico para BluRay
                    valorLocacao = bluray->calcularValorLocacao(dias);
                }
            } else if (filme->getTipo() == Filme::Tipo::Fita) {
                Fita* fita = dynamic_cast<Fita*>(filme);
                if (fita) {
                    // Calcula o valor de locação específico para Fita
                    valorLocacao = fita->calcularValorLocacao(dias);
                }
            }

            totalPagar += valorLocacao;
        }

        if (!filmes_alugados.empty()) {
            for (Filme* filme : filmes_alugados) {
                cliente->devolverFilmeAlugado(filme);
            }
        } else {
            throw std::out_of_range("Erro: Lista de filmes vazia.");
        }
 
        std::cout << "Total a pagar: ";
       
        std::cout << totalPagar << std::endl;
    } 
}

//métodos para cadastrar ou remover filmes do catálogo

void Locacao::cadastrarFilme(Filme* filme) {
    // Verifica se já existe um filme com o mesmo código
    auto it = std::find_if(_catalogo_filmes.begin(), _catalogo_filmes.end(),
                           [filme](Filme* f) { return f->getCodigo() == filme->getCodigo(); });

    if (it != _catalogo_filmes.end()) {
        // Filme com o mesmo código encontrado, adicione a quantidade disponível
        (*it)->adicionarUnidades(filme->getUnidadesDisponiveis());
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
        throw std::invalid_argument("Erro: Filme não encontrado.");
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
        throw std::invalid_argument("Erro: Cliente não encontrado.");
    }
}

//métodos para listar filmes e clientes

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

void Locacao::listarClientes() {
    for (Cliente* cliente : _clientes_cadastrados) {
        cliente->MostrarInfo();
    }
}

