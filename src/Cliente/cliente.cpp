#include "cliente.hpp"
#include <algorithm>

/**
 * @file cliente.cpp
 * @brief Implementação dos métodos da classe Cliente.
 */

/**
 * @brief Construtor da classe Cliente.
 * 
 * @param nome Nome do cliente.
 * @param cpf CPF do cliente.
 */
Cliente::Cliente(string nome, string cpf) : _nome(nome), _cpf(cpf), _pontos_fidelidade(0) {}

/**
 * @brief Destrutor da classe Cliente.
 */
Cliente::~Cliente() {}

/**
 * @brief Exibe as informações do cliente, incluindo nome, CPF e pontos de fidelidade.
 */
void Cliente::mostrarInfo() {
     cout << "Nome: " << this->_nome << endl;
     cout << "CPF: " << this->_cpf << endl;
     cout << "Pontos: " << this->_pontos_fidelidade << endl;
     // Filmes alugados
}

/**
 * @brief Adiciona pontos de fidelidade ao cliente.
 * 
 * @param pontos Quantidade de pontos a serem adicionados.
 */
void Cliente::adicionarPontos(int pontos) {
     this->_pontos_fidelidade += pontos;
     std::cout << "Total de pontos de fidelidade adquiridos nessa operação: " << pontos << std::endl; 
     std::cout << "Total de pontos de fidelidade acumulados: " << getPontos() << std::endl; 
}

/**
 * @brief Zera os pontos de fidelidade do cliente.
 */
void Cliente::zerarPontos() {
     this->_pontos_fidelidade = 0;
}

/**
 * @brief Obtém a quantidade de pontos de fidelidade do cliente.
 * 
 * @return Quantidade de pontos de fidelidade.
 */
int Cliente::getPontos() {
     return (this->_pontos_fidelidade);
}

/**
 * @brief Obtém o nome do cliente.
 * 
 * @return Nome do cliente.
 */
string Cliente::getNome() {
     return this->_nome;
}

/**
 * @brief Obtém o CPF do cliente.
 * 
 * @return CPF do cliente.
 */
string Cliente::getCpf() {
     return this->_cpf;
}

/**
 * @brief Obtém a lista de filmes alugados pelo cliente.
 * 
 * @return Vetor contendo os filmes alugados.
 */
vector<Filme*>& Cliente::getFilmesAlugados() {
     return this->_filmes_alugados;
}

/**
 * @brief Adiciona um filme à lista de filmes alugados pelo cliente.
 * 
 * @param filme Ponteiro para o filme a ser adicionado.
 */
void Cliente::adicionarFilmeAlugado(Filme* filme) {
    _filmes_alugados.push_back(filme);
}

/**
 * @brief Devolve todos os filmes alugados pelo cliente.
 */
void Cliente::devolverFilmesAlugados() {
     _filmes_alugados.clear();
}
