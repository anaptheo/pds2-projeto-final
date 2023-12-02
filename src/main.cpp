/**
 * @file main.cpp
 * @brief Arquivo principal para o programa Locadora PDS.
 */

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

/**
 * @brief Função principal para o programa Locadora PDS.
 * @return 0 em execução bem-sucedida.
 */
int main() {
    string input;
    Sistema sistema;

    // Apresentação do programa
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

    // Loop principal do programa
    while (true) {
        // Solicitação de comando ao usuário
        cout << "Digite um comando (digite 'ajuda' para os comandos): ";
        cin >> input;
        input = toUpperCase(input);
        try {
            // Verifica e executa o comando inserido
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
                // Mensagem de despedida e encerramento do programa
                cout << "\n===================================" << endl;
                cout << "   Obrigado por utilizar a Locadora PDS!" << endl;
                cout << "    Esperamos te ver novamente em breve." << endl;
                cout << "        Tenha um otimo dia!" << endl;
                cout << "===================================\n" << endl;

                break;
            } else if (input == "LA") {
                sistema.lerArquivo();
            } else {
                // Lança exceção se o comando for inválido
                throw std::invalid_argument("ERRO: Comando invalido. Digite 'ajuda' para ver os comandos.");
            }
        } 
        catch (std::exception& e) {
            // Exibe mensagem de erro se ocorrer uma exceção
            cerr << e.what() << endl;
        }
    }

    return 0;
}
