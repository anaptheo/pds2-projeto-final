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
    void devolverFilme(Cliente* cliente, std::vector<Filme*>& filmes, int dias);
    void alugarFilmes(const std::string& cpf, std::vector<Filme*>& filmes, int dias);
    void ImprimirFilmes();
    void adicionarFilmeAlugado(Filme* filme);
    void devolverFilmes(const std::string& cpf, const std::vector<Filme*>& filmes);
    void cadastrarFilme(Filme* filme);
    void removerFilme(int codigo);
    void listarFilmes();
    void listarFilmesTitulo();
    void cadastrarCliente(const std::string& nome, const std::string& cpf);
    void removerCliente(const std::string& cpf);
    void listarClientes();
    void listarClientesOrdenado();
    void alugarFilmes(const std::string& cpf, std::vector<int> codigos, int dias);
    void devolverFilmes(const std::string& cpf, const std::vector<int>& codigos);
    Cliente* getCliente(const std::string& cpf);
    Filme* getFilme(int codigo_filme);
};

#endif // LOCACAO_HPP
