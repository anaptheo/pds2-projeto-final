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
        void devolverFilme(Cliente* cliente); 
        void alugarFilme(Cliente* cliente, vector<Filme*> filmes); 
        void ImprimirFilmes(); 
        Filme* getFilme(int codigo_filme);
};

#endif // LOCACAO_HPP
