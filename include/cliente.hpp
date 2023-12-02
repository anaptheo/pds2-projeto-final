#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <vector>

#include "filme.hpp"

using namespace std;

/**
 * @file cliente.hpp
 * @brief Declaração da classe Cliente, seus métodos e atributos.
 * @details Este arquivo define a classe Cliente, que representa um cliente do sistema de locação de filmes.
 * @class Cliente
 * @details A classe Cliente possui atributos como nome, CPF, pontos de fidelidade e uma lista de filmes alugados.
 *          Além disso, contém métodos para exibir informações do cliente, adicionar pontos de fidelidade, zerar pontos,
 *          obter nome, CPF, lista de filmes alugados e pontos de fidelidade, adicionar filme à lista de filmes alugados
 *          e devolver todos os filmes alugados.
 * @param _nome Nome do cliente.
 * @param _cpf CPF do cliente.
 * @param _pontos_fidelidade Pontos de fidelidade acumulados pelo cliente.
 * @param _filmes_alugados Lista de filmes alugados pelo cliente.
 */

class Cliente
{
private:
     string _nome; /**< Nome do cliente. */
     string _cpf; /**< CPF do cliente. */
     int _pontos_fidelidade; /**< Pontos de fidelidade acumulados pelo cliente. */
     bool _alugou_aparelho; /**< Indica se cliente tem aparelho alugado ou não. */
     vector <Filme*> _filmes_alugados; /**< Lista de filmes alugados pelo cliente. */

public:
     /**
      * @brief Construtor da classe Cliente.
      * @param nome Nome do cliente.
      * @param cpf CPF do cliente.
      */
     Cliente(string nome, string cpf);

     /**
      * @brief Destrutor da classe Cliente.
      */
     ~Cliente();

     /**
      * @brief Exibe informações do cliente.
      */
     void mostrarInfo();

     /**
      * @brief Adiciona pontos de fidelidade ao cliente.
      * @param pontos Pontos a serem adicionados.
      */
     void adicionarPontos(int pontos);

     /**
      * @brief Usa os pontos de fidelidade do cliente.
      */
     void usarPontos();

     // Getters

     /**
      * @brief Obtém o nome do cliente.
      * @return Nome do cliente.
      */
     string getNome();

     /**
      * @brief Obtém o status de alugel de aparelho do cliente.
      * @return Bool do status.
      */
     bool getAparelhoAlugado();

     /**
      * @brief Obtém o CPF do cliente.
      * @return CPF do cliente.
      */
     string getCpf();

     /**
      * @brief Obtém a lista de filmes alugados pelo cliente.
      * @return Lista de filmes alugados.
      */
     vector<Filme*>& getFilmesAlugados();

     /**
      * @brief Obtém os pontos de fidelidade do cliente.
      * @return Pontos de fidelidade.
      */
     int getPontos();

     /**
      * @brief Adiciona um filme à lista de filmes alugados pelo cliente.
      * @param filme Filme a ser adicionado.
      */
     void adicionarFilmeAlugado(Filme* filme);

     /**
      * @brief Devolve todos os filmes alugados pelo cliente.
      */
     void devolverFilmesAlugados();

     /**
      * @brief Aluga o aparelho solicitado pelo cliente.
      */
     void alugarAparelhoBluray();

     /**
      * @brief Devolve o aparelho alugado pelo cliente.
      */
     void devolverAparelhoBluray();
};

#endif // CLIENTE_H