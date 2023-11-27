#include <iostream>
#include <string>
#include "locacao.hpp"

#include "dvd.hpp"
#include "bluray.hpp"
#include "fita.hpp"

using namespace std;

int main() {
    string input;
    Locacao locacao;
    Categoria categoria;

    cout << "Bem-vindo ao Sistema de Locadora de Vídeos!" << endl;

    while (true) {
        cout << "Digite um comando (digite 'ajuda' para os comandos): ";
        cin >> input;

        if (input == "ajuda") {
            // colocar
        } else if (input == "CF") {
            char tipo;
            cout << "Digite o tipo do filme (D para DVD, B para Bluray, F para Fita): ";
            cin >> tipo;

            Filme* filme;
            if (tipo == 'D') {
                int codigo, quantidade;
                string titulo;

                cout << "Digite o código do DVD: ";
                cin >> codigo;
                cout << "Digite o título do DVD: ";
                cin >> titulo;
                cout << "Digite a quantidade de DVDs: ";
                cin >> quantidade;
                cout << "Digite a categoria do DVD (L para Lançamento, E para Estoque, P para Promoção): ";
                char categoriaChar;
                cin >> categoriaChar;

                switch (categoriaChar) {
                    case 'L':
                        categoria = Categoria::Lancamento;
                        break;
                    case 'E':
                        categoria = Categoria::Estoque;
                        break;
                    case 'P':
                        categoria = Categoria::Promocao;
                        break;
                    default:
                        cout << "Categoria inválida." << endl;
                        continue;
                }
                
                filme = new DVD(titulo, codigo, quantidade, categoria);

            } else if (tipo == 'B') {
                int codigo, quantidade;
                string titulo;

                cout << "Digite o código do Bluray: ";
                cin >> codigo;
                cout << "Digite o título do Bluray: ";
                cin >> titulo;
                cout << "Digite a quantidade de Blurays: ";
                cin >> quantidade;

                filme = new Bluray(titulo, codigo, quantidade);
            } else if (tipo == 'F') {
                int codigo, quantidade;
                string titulo;
                bool rebobinada;

                cout << "Digite o código da Fita: ";
                cin >> codigo;
                cout << "Digite o título da Fita: ";
                cin >> titulo;
                cout << "Digite a quantidade de Fitas: ";
                cin >> quantidade;
                cout << "A Fita está rebobinada? (1 para Sim, 0 para Não): ";
                cin >> rebobinada;

                filme = new Fita(titulo, codigo, quantidade, rebobinada);
            } else {
                cout << "Tipo de filme inválido." << endl;
                continue;
            }

            cout << "Filme cadastrado com sucesso!" << endl;

        } else if (input == "RF") {
            int codigo;
            cout << "Digite o código do filme a ser removido: ";
            cin >> codigo;
            locacao.removerFilme(codigo);

        } else if (input == "LF") {
            cout << "Listando filmes:" << endl;
            locacao.listarFilmes();

        } else if (input == "CC") {
            string nome, cpf;
            cout << "Digite o nome do cliente: ";
            cin >> nome;
            cout << "Digite o CPF do cliente: ";
            cin >> cpf;
            locacao.cadastrarCliente(nome, cpf);

        } else if (input == "RC") {
            string cpf;
            cout << "Digite o CPF do cliente a ser removido: ";
            cin >> cpf;
            locacao.removerCliente(cpf);

        } else if (input == "LC") {
            cout << "Listando clientes:" << endl;
            locacao.listarClientes();

        } else if (input == "AL") {
            string cpf;
            int codigo1, codigo2; // ?
            cout << "Digite o CPF do cliente: ";
            cin >> cpf;
            cout << "Digite os códigos dos filmes a serem alugados (separados por espaço): ";
            cin >> codigo1 >> codigo2; // ?
            locacao.alugarFilmes(cpf, codigo1, codigo2);

        } else if (input == "DV") {
            string cpf;
            cout << "Digite o CPF do cliente que está devolvendo os filmes: ";
            cin >> cpf;
            locacao.devolverFilmes(cpf);

        } else if (input == "FS") {
            cout << "Encerrando o Sistema de Locadora de Vídeos. Até logo!" << endl;
            break;

        } else {
            cout << "Comando inválido. Digite 'ajuda' para ver os comandos." << endl;
        }
    }

    return 0;
}
