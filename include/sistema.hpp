#ifndef SISTEMA_H
#define SISTEMA_H

#include "locacao.hpp"
#include "filme.hpp"

class Sistema {
    private:
        Locacao _locacao;
        vector<Filme*> filmes;
    public:
        Sistema();
        void displayHelp();
        void cadastrarFilme();
        void cadastrarCliente();
        void removerCliente();
        void removerFilme();
        void listarFilmes();
        void listarClientes();
        void devolverFilmes();
        void alugarFilmes();
        void lerArquivo();
};

#endif