#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "locacao.hpp"
#include "dvd.hpp"
#include "bluray.hpp"
#include "fita.hpp"

using namespace std;

void displayHelp() {
    cout << "Comandos disponiveis:" << endl;
    cout << "CF - Cadastrar Filme: Adiciona um filme ao catálogo da locadora." << endl;
    cout << "RF - Remover Filme: Remove um filme do catálogo da locadora." << endl;
    cout << "LF - Listar Filmes: Lista todos os filmes disponíveis na locadora." << endl;
    cout << "CC - Cadastrar Cliente: Adiciona um cliente à lista de clientes da locadora." << endl;
    cout << "RC - Remover Cliente: Remove um cliente da lista de clientes da locadora." << endl;
    cout << "LC - Listar Clientes: Lista todos os clientes cadastrados na locadora." << endl;
    cout << "AL - Alugar Filme: Permite alugar filmes para um cliente." << endl;
    cout << "DV - Devolver Filme: Devolve filmes alugados por um cliente." << endl;
    cout << "FS - Finalizar Sistema: Encerra o Sistema de Locadora de Vídeos." << endl;
    cout << "ajuda - Exibir este menu de ajuda." << endl;
}

void printError(const string& error) {
    cout << "ERRO: " << error << endl;
}

int main() {
    string input;
    Locacao locacao;
    Categoria categoria;
    string cpf;
    int codigo;
    int dias;
    vector<Filme*> filmes;

    while (true) {
        cout << "Digite um comando (digite 'ajuda' para os comandos): ";
        getline(cin, input);

        istringstream iss(input);
        string command;
        iss >> command;

        if (command == "ajuda") {
            displayHelp();
        } else if (command == "CF") {
            char tipo;
            iss >> tipo;

            Filme* filme;
            Categoria categoria;

            if (tipo == 'D') {
                int codigo, quantidade;
                string titulo;
                char categoriaChar;
                iss >> codigo >> quantidade >> titulo >> categoriaChar;

                if (categoriaChar == 'L' || categoriaChar == 'E' || categoriaChar == 'P') {
                    if (categoriaChar == 'L') {
                        categoria = Categoria::Lancamento;
                    } else if (categoriaChar == 'E') {
                        categoria = Categoria::Estoque;
                    } else if (categoriaChar == 'P') {
                        categoria = Categoria::Promocao;
                    }

                    filme = new DVD(titulo, codigo, quantidade, categoria);
                    locacao.cadastrarFilme(filme);
                } else {
                    printError("Categoria inválida.");
                    continue;
                }
            } else if (tipo == 'B') {
                int codigo, quantidade;
                string titulo;
                iss >> codigo >> quantidade >> titulo;

                filme = new Bluray(titulo, codigo, quantidade);
                locacao.cadastrarFilme(filme);

            } else if (tipo == 'F') {
                int codigo, quantidade;
                string titulo;
                bool rebobinada;
                iss >> codigo >> quantidade >> titulo >> rebobinada;

                filme = new Fita(titulo, codigo, quantidade, rebobinada);
                locacao.cadastrarFilme(filme);

            } else {
                printError("Tipo de filme inválido.");
                continue;
            }

            cout << "Filme cadastrado com sucesso" << endl;

        } else if (command == "RF") {
            iss >> codigo;
            locacao.removerFilme(codigo);

        } else if (command == "LF") {
            locacao.listarFilmes();

        } else if (command == "CC") {
            string nome, cpf;
            getline(iss, nome);
            iss >> cpf;
            locacao.cadastrarCliente(nome, cpf);

        } else if (command == "RC") {
            iss >> cpf;
            locacao.removerCliente(cpf);

        } else if (command == "LC") {
            locacao.listarClientes();

        } else if (command == "AL") {
            iss >> cpf;
            Cliente* cliente = locacao.getCliente(cpf);

            if (cliente != nullptr) {
                while (true) {
                    iss >> codigo;

                    if (codigo == -1) {
                        break;
                    }

                    Filme* filme = locacao.getFilme(codigo);

                    if (filme != nullptr) {
                        filmes.push_back(filme);
                    } else {
                        printError("Filme código inexistente");
                    }
                }

                iss >> dias;
                locacao.alugarFilmes(cliente->getCpf(), filmes, dias);
                filmes.clear();
            } else {
                printError("CPF inexistente");
            }

        } else if (command == "DV") {
            iss >> cpf;
            Cliente* cliente = locacao.getCliente(cpf);

            if (cliente != nullptr) {
                locacao.devolverFilmes(cliente->getCpf(), filmes);
                filmes.clear();
            } else {
                printError("CPF inexistente");
            }

        } else if (command == "FS") {
            break;
        } else {
            printError("Comando inválido.");
        }
    }

    return 0;
}