#ifndef LOCACAO_HPP
#define LOCACAO_HPP

#include <iostream>
#include <vector>

#include "filme.hpp"
#include "cliente.hpp"

class Locacao {
protected:
    std::vector<Filme*> _catalogo_filmes;
    std::vector<Cliente*> _clientes_cadastrados;

public:
    void emiteReciboAluguel(Cliente* cliente);
    void emiteReciboDevolucao(Cliente* cliente, int dias);
    void devolverFilme(Cliente* cliente, std::vector<Filme*> filmes, int dias);
    void alugarFilme(Cliente* cliente, std::vector<Filme*> filmes, int dias);
    void ImprimirFilmes();
    Filme* getFilme(int codigo_filme);
    void adicionarFilmeAlugado(Filme* filme);
    void devolverFilmeAlugado(Filme* filme);
    void cadastrarFilme(Filme* filme);
    void removerFilme(int codigo);
    void listarFilmes();
    void cadastrarCliente(const std::string& nome, const std::string& cpf);
    void removerCliente(const std::string& cpf);
    void listarClientes();
    void alugarFilmes(const std::string& cpf, int codigo1, int codigo2);
    void devolverFilmes(const std::string& cpf);
};

#endif // LOCACAO_HPP
