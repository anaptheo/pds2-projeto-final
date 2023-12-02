/**
 * @file locacao.cpp
 * @brief Implementação dos métodos da classe Locacao.
 */

#include "locacao.hpp"
#include "dvd.hpp"
#include "bluray.hpp"
#include "fita.hpp"
#include <algorithm>
#include <iostream>

// Getters para retornar filme/cliente por código/cpf

/**
 * @brief Retorna um ponteiro para um Filme com base no código fornecido.
 * 
 * @param codigo_filme Código do filme a ser encontrado.
 * @return Ponteiro para o Filme encontrado ou nullptr se não for encontrado.
 */
Filme* Locacao::getFilme(std::string codigo_filme) {
    for (auto filme : _catalogo_filmes) {
        if (filme->getCodigo() == codigo_filme) {
            return filme;
        }
    }
    return nullptr;
}

/**
 * @brief Retorna um ponteiro para um Cliente com base no CPF fornecido.
 * 
 * @param cpf CPF do cliente a ser encontrado.
 * @return Ponteiro para o Cliente encontrado ou nullptr se não for encontrado.
 */
Cliente* Locacao::getCliente(const std::string& cpf) {
    auto it = std::find_if(_clientes_cadastrados.begin(), _clientes_cadastrados.end(),
                            [cpf](Cliente* cliente) { return cliente->getCpf() == cpf; });

    return (it != _clientes_cadastrados.end()) ? *it : nullptr;
}

// Impressão dos recibos

/**
 * @brief Emite um recibo de aluguel para o cliente.
 * 
 * @param cliente Ponteiro para o cliente que alugou os filmes.
 * @param filmes Vetor de ponteiros para os filmes alugados.
 */
void Locacao::emiteReciboAluguel(Cliente* cliente, std::vector<Filme*>& filmes) {
    std::cout << "Cliente " << cliente->getCpf() << " " << cliente->getNome() << " alugou os filmes:" << std::endl; 
    for (auto filme : filmes) {
        std::cout << filme->getCodigo() << " " << filme->getTitulo() << " " << filme->getTipo() << std::endl;
    }
}

/**
 * @brief Emite um recibo de devolução para o cliente.
 * 
 * @param cliente Ponteiro para o cliente que devolveu os filmes.
 * @param dias Número de dias pelos quais os filmes foram alugados.
 */
void Locacao::emiteReciboDevolucao(Cliente* cliente, int dias) {
    std::cout << "Cliente " << cliente->getCpf() << " " << cliente->getNome() << " devolveu os filmes:" << std::endl; 
    
    int valor_total = 0;
    for (auto filme : cliente->getFilmesAlugados()) {
        int valor_pagamento = filme->calcularValorLocacao(dias);
        std::cout << filme->getCodigo() << " " << valor_pagamento << std::endl;
        valor_total += valor_pagamento;
    }
    // Valor fixo para locação de Blu-ray
    if (cliente->getAparelhoAlugado() == true) {
        valor_total += 20;
        cliente->devolverAparelhoBluray();
        std::cout << "e um aparelho de bluray." << std::endl;
    }
    // novo metodo de cliente checaDescontoFidelidade
    if (cliente->getPontos() >= 5) {
        std::cout << "PARABÉNS! Você já acumulou 5 pontos de fidelidade, então ganhou um desconto de R$ 10,00 no seu aluguel de hoje. Aproveite!" << std::endl;
        
        cliente->usarPontos();
        valor_total -= 10;
    }
    std::cout << "Total a pagar: " << valor_total << std::endl;
}

// Métodos para alugar e devolver filmes

/**
 * @brief Realiza a locação de filmes para um cliente.
 * 
 * @param cpf CPF do cliente que deseja alugar os filmes.
 * @param filmes_a_alugar Vetor de ponteiros para os filmes que o cliente deseja alugar.
 */
void Locacao::alugarFilmes(const std::string& cpf, std::vector<Filme*>& filmes_a_alugar) {
    Cliente* cliente = getCliente(cpf);
    int totalPontosFidelidade = 0;

    std::vector<Filme*> filmes_alugados;
    for (Filme* filme : filmes_a_alugar) {
        if (filme->getUnidadesDisponiveis() > 0 ) {
            cliente->adicionarFilmeAlugado(filme);
            filme->removerUnidadeDisponivel();

            filmes_alugados.push_back(filme);
            totalPontosFidelidade++;
        } else {
            cout << "Não foi possível alugar o filme " << filme->getTitulo()
            << " pois todos os filmes desse tipo estão alugados."<< endl;
            }
        }

    if (filmes_alugados.size() > 0) {
        emiteReciboAluguel(cliente, filmes_alugados);
        cliente->adicionarPontos(totalPontosFidelidade);
        // Limpar o vetor após o aluguel
        filmes_a_alugar.clear();
    }
}

/**
 * @brief Realiza a devolução de filmes por um cliente.
 * 
 * @param cliente Ponteiro para o cliente que está devolvendo os filmes.
 * @param dias Número de dias pelos quais os filmes foram alugados.
 */
void Locacao::devolverFilmes(Cliente* cliente, int dias) {
    emiteReciboDevolucao(cliente, dias);
    cliente->devolverFilmesAlugados();
}

// Métodos para cadastrar ou remover filmes do catálogo

/**
 * @brief Cadastra um novo filme no catálogo.
 * 
 * @param filme Ponteiro para o filme a ser cadastrado.
 */
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

/**
 * @brief Remove um filme do catálogo com base no código fornecido.
 * 
 * @param codigo Código do filme a ser removido.
 * @throws std::invalid_argument se o filme não for encontrado.
 */
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

/**
 * @brief Cadastra um novo cliente no sistema.
 * 
 * @param nome Nome do cliente a ser cadastrado.
 * @param cpf CPF do cliente a ser cadastrado.
 */
void Locacao::cadastrarCliente(const std::string& nome, const std::string& cpf) {
    _clientes_cadastrados.push_back(new Cliente(nome, cpf));
    std::cout << "Cliente cadastrado com sucesso!" << std::endl;
}

/**
 * @brief Remove um cliente do sistema com base no CPF fornecido.
 * 
 * @param cpf CPF do cliente a ser removido.
 * @throws std::invalid_argument se o cliente não for encontrado.
 */
void Locacao::removerCliente(const std::string& cpf) {
    auto it = std::remove_if(_clientes_cadastrados.begin(), _clientes_cadastrados.end(),
                             [cpf](Cliente* cliente) { return cliente->getCpf() == cpf; });

    if (it != _clientes_cadastrados.end()) {
        _clientes_cadastrados.erase(it, _clientes_cadastrados.end());
        std::cout << "Cliente removido com sucesso!" << endl;
    } else {
        throw std::invalid_argument("ERRO: Cliente não encontrado.");
    }
}

/**
 * @brief Lista os filmes ordenados por código.
 */
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

/**
 * @brief Lista os filmes ordenados por título.
 */
void Locacao::listarFilmesTitulo() {

    // Ordena os filmes por título
    std::sort(_catalogo_filmes.begin(), _catalogo_filmes.end(), [](Filme* a, Filme* b) {
        if (a->getTitulo().compare(b->getTitulo()) < 0 ){
            return true;
        } else if (a->getTitulo().compare(b->getTitulo()) > 0 ){
            return false;
        } 
        return true;
    });

    // Exibe os filmes
    for (Filme* filme : _catalogo_filmes) {
        std::cout << "Codigo: " << filme->getCodigo() << " - Titulo: " << filme->getTitulo()
                  << " - Quantidade: " << filme->getUnidadesDisponiveis() << " - Tipo: " << filme->getTipo() << std::endl;
    }
}

/**
 * @brief Lista os clientes ordenados por código.
 */
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

/**
 * @brief Lista os clientes ordenados por nome.
 */
void Locacao::listarClientesNome(){
    std::sort(_clientes_cadastrados.begin(), _clientes_cadastrados.end(), [](Cliente* a, Cliente* b) {
        if (a->getNome().compare(b->getNome()) < 0 ){
            return true;
        } else if (a->getNome().compare(b->getNome()) > 0 ){
            return false;
        }
        return true;
    });
    for (Cliente* cliente : _clientes_cadastrados) {
        cliente->mostrarInfo();
    }
}