#ifndef SISTEMA_H
#define SISTEMA_H

#include "locacao.hpp"
#include "filme.hpp"

/**
 * @file sistema.hpp
 * @brief Declaração da classe Sistema e seus métodos.
 */

/**
 * @brief Classe que representa o sistema de locação de filmes.
 * 
 * A classe Sistema gerencia as operações do sistema de locação, interagindo com a classe Locacao.
 */
class Sistema {
private:
    Locacao _locacao; /**< Objeto da classe Locacao que gerencia as operações de locação. */
    vector<Filme*> filmes; /**< Vetor que armazena os filmes cadastrados no sistema. */

public:
    /**
     * @brief Construtor da classe Sistema.
     * 
     * Inicializa uma instância da classe Sistema.
     */
    Sistema();

    /**
     * @brief Exibe informações de ajuda sobre os comandos disponíveis no sistema.
     */
    void displayHelp();

    /**
     * @brief Realiza a operação de cadastrar um novo filme no sistema.
     */
    void cadastrarFilme(std::deque<std::string> lista_input);

    /**
     * @brief Realiza a operação de cadastrar um novo cliente no sistema.
     */
    void cadastrarCliente(std::deque<std::string> lista_input);

    /**
     * @brief Realiza a operação de remover um cliente do sistema.
     */
    void removerCliente(std::deque<std::string> lista_input);

    /**
     * @brief Realiza a operação de remover um filme do sistema.
     */
    void removerFilme(std::deque<std::string> lista_input);

    /**
     * @brief Lista os filmes cadastrados no sistema.
     */
    void listarFilmes(std::deque<std::string> lista_input);

    /**
     * @brief Lista os clientes cadastrados no sistema.
     */
    void listarClientes(std::deque<std::string> lista_input);

    /**
     * @brief Realiza a operação de devolução de filmes por parte do cliente.
     */
    void devolverFilmes(std::deque<std::string> lista_input);

    /**
     * @brief Realiza a operação de aluguel de filmes para um cliente.
     */
    void alugarFilmes(std::deque<std::string> lista_input);

    /**
     * @brief Realiza a leitura de informações de arquivo para inicializar o sistema.
     */
    void lerArquivo(string nome_arquivo);

    /**
     * @brief Gerencia o sistema com base no input do usuário.
     */
    bool gerenciaOpcoes(string comando, std::deque<std::string> lista_input);
    
    /**
     * @brief Recebe o input em linha e retorna uma tupla contendo uma string com a operação a 
     * ser realizada e um deque com os comandos restantes.
     */
    std::tuple<std::string, std::deque<std::string>> processaInput(std::string input);
};

#endif // SISTEMA_H
