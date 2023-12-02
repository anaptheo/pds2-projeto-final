#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>
#include <vector>

#include "filme.hpp"

using namespace std;

class Cliente
{
private:
     string _nome;
     string _cpf;
     int _pontos_fidelidade;
     bool _alugou_aparelho;
     vector <Filme*> _filmes_alugados;
public:
     Cliente(string nome, string cpf);
     ~Cliente();

     void mostrarInfo();
     void adicionarPontos(int pontos);
     void usarPontos();

     // Getters
     string getNome();
     string getCpf();
     bool getAparelhoAlugado();
     vector<Filme*>& getFilmesAlugados();
     int getPontos();
     void adicionarFilmeAlugado(Filme* filme);
     void devolverFilmesAlugados();
     void alugarAparelhoBluray();
     void devolverAparelhoBluray();
};

#endif
