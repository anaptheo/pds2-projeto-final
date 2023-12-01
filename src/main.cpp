#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <iomanip>

#include "locacao.hpp"
#include "dvd.hpp"
#include "bluray.hpp"
#include "fita.hpp"
#include "formatacao.hpp"
#include "sistema.hpp"

using namespace std;

int main() {
    string input;
    Sistema sistema;

    cout << setw(50) << setfill('=') << "" << endl;
    cout << setw(10) << "        Bem-vindo a Locadora PDS!  " << endl;
    cout << setw(50) << "" << endl;
    cout << endl;
    cout << "  Explore nosso catalogo e aproveite a variedade de filmes disponiveis." << endl;
    cout << endl;
    cout << "  Oferecemos DVDs, Blu-rays e Fitas para atender a todos os gostos." << endl;
    cout << endl;
    cout << "  Cadastre filmes, clientes, alugue e devolva filmes de forma facil e rapida." << endl;
    cout << endl;
    cout << setw(50) << "" << endl;
    cout << "  Digite 'ajuda' a qualquer momento para ver os comandos disponiveis." << endl;
    cout << setw(50) << setfill('=') << "" << endl;
    cout << endl;


    while (true) {
        cout << "Digite um comando (digite 'ajuda' para os comandos): ";
        cin >> input;
        input = toUpperCase(input);
        try {
            if (input == "AJUDA") {
                sistema.displayHelp();
            } else if (input == "CF") {
                sistema.cadastrarFilme();
            } else if (input == "RF") {
                sistema.removerFilme();
            } else if (input == "LF") {
                sistema.listarFilmes();
            } else if (input == "CC") {
                sistema.cadastrarCliente();
            } else if (input == "RC") {
                sistema.removerCliente();
            } else if (input == "LC") {
                sistema.listarClientes();
            } else if (input == "AL") {
                sistema.alugarFilmes();
            } else if (input == "DV") {
                sistema.devolverFilmes();
            } else if (input == "FS") {
                cout << "\n===================================" << endl;
                cout << "   Obrigado por utilizar a Locadora PDS!" << endl;
                cout << "    Esperamos te ver novamente em breve." << endl;
                cout << "        Tenha um otimo dia!" << endl;
                cout << "===================================\n" << endl;

                break;
            } else if (input == "LA") {
                sistema.lerArquivo();
            } else {
                //SERA Q precisa disso? acho q ganha pontos extras ne na defensividade
                throw std::invalid_argument("ERRO: Comando invalido. Digite 'ajuda' para ver os comandos.");
            }
        } 
        catch (std::exception& e) {
            cerr << e.what() << endl;
        }
    }

    return 0;
}