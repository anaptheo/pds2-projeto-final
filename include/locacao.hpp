#ifndef LOCACAO_HPP
#define LOCACAO_HPP

#include <iostream>
#include <vector>

#include "filme.hpp"
#include "cliente.hpp"

/**
 * @file locacao.hpp

 * @brief Classe responsável por gerenciar as operações de locação de filmes.
 * 
 * @details classe Locacao realiza o cadastro, remoção, aluguel e devolução de filmes, além de manter registros
 * dos filmes disponíveis no catálogo e dos clientes cadastrados.
 */

class Locacao {
protected:
    std::vector<Filme*> _catalogo_filmes; /**< Vetor que armazena os filmes disponíveis para locação. */
    std::vector<Cliente*> _clientes_cadastrados; /**< Vetor que armazena os clientes cadastrados no sistema. */

public:
    /**
     * @brief Cadastra um novo filme no catálogo.
     * 
     * @param filme Ponteiro para o filme a ser cadastrado.
     */
    void cadastrarFilme(Filme* filme);

    /**
     * @brief Remove um filme do catálogo pelo código.
     * 
     * @param codigo Código do filme a ser removido.
     */
    void removerFilme(std::string codigo);

    /**
     * @brief Realiza o aluguel de filmes para um cliente.
     * 
     * @param cpf CPF do cliente.
     * @param filmes Vetor de ponteiros para os filmes a serem alugados.
     */
    void alugarFilmes(const std::string& cpf, std::vector<Filme*>& filmes);

    /**
     * @brief Emite o recibo de aluguel para um cliente.
     * 
     * @param cliente Ponteiro para o cliente.
     * @param filmes Vetor de ponteiros para os filmes alugados.
     */
    void emiteReciboAluguel(Cliente* cliente, std::vector<Filme*>& filmes);

    /**
     * @brief Realiza a devolução de filmes por parte do cliente.
     * 
     * @param cliente Ponteiro para o cliente.
     * @param dias Número de dias pelos quais os filmes foram alugados.
     */
    void devolverFilmes(Cliente* cliente, int dias);

    /**
     * @brief Emite o recibo de devolução para um cliente.
     * 
     * @param cliente Ponteiro para o cliente.
     * @param dias Número de dias pelos quais os filmes foram alugados.
     */
    void emiteReciboDevolucao(Cliente* cliente, int dias);

    /**
     * @brief Lista os filmes cadastrados no sistema ordenados por código.
     */
    void listarFilmesCodigo();

    /**
     * @brief Lista os filmes cadastrados no sistema ordenados por título.
     */
    void listarFilmesTitulo();
    
    /**
     * @brief Cadastra um novo cliente no sistema.
     * 
     * @param nome Nome do cliente.
     * @param cpf CPF do cliente.
     */
    void cadastrarCliente(const std::string& nome, const std::string& cpf);

    /**
     * @brief Remove um cliente do sistema pelo CPF.
     * 
     * @param cpf CPF do cliente a ser removido.
     */
    void removerCliente(const std::string& cpf);

    /**
     * @brief Lista os clientes cadastrados no sistema ordenados por código.
     */
    void listarClientesCodigo();

    /**
     * @brief Lista os clientes cadastrados no sistema ordenados por nome.
     */
    void listarClientesNome();

    /**
     * @brief Obtém um cliente pelo CPF.
     * 
     * @param cpf CPF do cliente.
     * @return Ponteiro para o cliente encontrado, ou nullptr se não encontrado.
     */
    Cliente* getCliente(const std::string& cpf);

    /**
     * @brief Obtém um filme pelo código.
     * 
     * @param codigo_filme Código do filme.
     * @return Ponteiro para o filme encontrado, ou nullptr se não encontrado.
     */
    Filme* getFilme(std::string codigo_filme);
};

#endif // LOCACAO_HPP
