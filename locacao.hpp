#ifndef LOCACAO_HPP
#define LOCACAO_HPP

#include <iostream>
#include <vector>

#include "filme.hpp"
#include "cliente.hpp"

class Locacao {
    protected:
        vector<Filme*> _catalogo_filmes;
        vector<Cliente*> _clientes_cadastrados;
    public:
        void emiteReciboAluguel(Cliente* cliente); 
        void emiteReciboDevolucao(Cliente* cliente, int dias); 
        void devolverFilme(Cliente* cliente, vector<Filme*> filmes, int dias); 
        void alugarFilme(Cliente* cliente, vector<Filme*> filmes, int dias); 
        void ImprimirFilmes(); 
        Filme* getFilme(int codigo_filme);
        void adicionarFilmeAlugado(Filme* filme);
        void devolverFilmeAlugado(Filme* filme);
};

#endif // LOCACAO_HPP
