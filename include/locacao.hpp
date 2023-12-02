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

    void cadastrarFilme(Filme* filme);
    void removerFilme(std::string codigo);

    void alugarFilmes(const std::string& cpf, std::vector<Filme*>& filmes);
    void emiteReciboAluguel(Cliente* cliente, std::vector<Filme*>& filmes);

    void devolverFilmes(Cliente* cliente, int dias);
    void emiteReciboDevolucao(Cliente* cliente, int dias);

    void listarFilmesCodigo();
    void listarFilmesTitulo();
    
    void cadastrarCliente(const std::string& nome, const std::string& cpf);
    void removerCliente(const std::string& cpf);

    void listarClientesCodigo();
    void listarClientesNome();

    Cliente* getCliente(const std::string& cpf);
    Filme* getFilme(std::string codigo_filme);
    vector<Filme*> getvectorFilmes();
    vector<Cliente*> getvectorClientes(); 
};

#endif // LOCACAO_HPP
