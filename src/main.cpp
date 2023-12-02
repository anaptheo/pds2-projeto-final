/**
 * @file main.cpp
 * @brief Arquivo principal para o programa Locadora PDS.
 */

#include <iostream>
#include <string>
#include <deque>
#include <iomanip>

#include "formatacao.hpp"
#include "sistema.hpp"


using namespace std;

/**
 * @brief Função principal para o programa Locadora PDS.
 * @return 0 em execução bem-sucedida.
 */
int main() {
    string input;
    Sistema* sistema = new Sistema();
    bool encerra_sistema = false;

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
    while (!encerra_sistema) {
        cout << "Digite um comando (digite 'ajuda' para os comandos): ";
        std::getline(cin, input);

        std::deque<std::string> lista_input;
        string comando;
        tie(comando, lista_input) = sistema->processaInput(input);
        comando = toUpperCase(comando);
        encerra_sistema = sistema->gerenciaOpcoes(comando, lista_input);
    }

    return 0;
}