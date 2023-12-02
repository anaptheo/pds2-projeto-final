#ifndef SISTEMA_H
#define SISTEMA_H

#include "locacao.hpp"
#include "filme.hpp"

class Sistema {
    private:
        Locacao _locacao;
        vector<Filme*> filmes;
    public:
        void displayHelp();
        void cadastrarFilme(std::deque<std::string> lista_input);
        void cadastrarCliente(std::deque<std::string> lista_input);
        void removerCliente(std::deque<std::string> lista_input);
        void removerFilme(std::deque<std::string> lista_input);
        void listarFilmes(std::deque<std::string> lista_input);
        void listarClientes(std::deque<std::string> lista_input);
        void devolverFilmes(std::deque<std::string> lista_input);
        void alugarFilmes(std::deque<std::string> lista_input);
        bool controlaComando(string comando, std::deque<std::string> lista_input);
        void lerArquivo(string nome_arquivo);
        std::tuple<std::string, std::deque<std::string>> processaInput(std::string input);
};

#endif