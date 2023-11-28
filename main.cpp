#include <iostream>
#include <string>
#include "locacao.hpp"

#include "dvd.hpp"
#include "bluray.hpp"
#include "fita.hpp"

using namespace std;

void displayHelp() {
    cout << "Comandos disponíveis:" << endl;
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

int main() {
    string input;
    Locacao locacao;
    Categoria categoria;
    string cpf;
    int codigo;
    int dias;
    vector<Filme*> filmes;

    cout << "Bem-vindo ao Sistema de Locadora de Videos!" << endl;

    while (true) {
        cout << "Digite um comando (digite 'ajuda' para os comandos): ";
        cin >> input;

        if (input == "ajuda") {
            displayHelp();
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
            std::cout << "Digite o CPF do cliente: ";
            std::cin >> cpf;

            Cliente* cliente = locacao.getCliente(cpf);

            if (cliente != nullptr) {
                // Permitir que o usuário insira múltiplos códigos de filmes até indicar que terminou
                while (true) {
                    std::cout << "Digite o código do filme a ser alugado (ou -1 para encerrar): ";
                    std::cin >> codigo;

                    if (codigo == -1) {
                        break; // Sair do loop se -1 for inserido
                    }

                    Filme* filme = locacao.getFilme(codigo);

                    if (filme != nullptr) {
                        filmes.push_back(filme);
                    } else {
                        std::cout << "Filme código " << codigo << " não encontrado." << std::endl;
                    }
                }

                std::cout << "Digite a quantidade de dias para aluguel: ";
                std::cin >> dias;

                // Use locacao.alugarFilmes com o ponteiro Cliente obtido
                locacao.alugarFilmes(cliente->getCpf(), filmes, dias);

                // Limpar o vetor de filmes após o aluguel ser concluído
                filmes.clear();
            } else {
                std::cout << "Cliente não encontrado." << std::endl;
            }

        } else if (input == "DV") {
            std::cout << "Digite o CPF do cliente que está devolvendo os filmes: ";
            std::cin >> cpf;

            Cliente* cliente = locacao.getCliente(cpf);

            if (cliente != nullptr) {
                // Use locacao.devolverFilmes instead of locacao.devolverFilme
                locacao.devolverFilmes(cliente->getCpf(), filmes);

                // Limpar o vetor de filmes após a devolução ser concluída
                filmes.clear();
            } else {
                std::cout << "Cliente não encontrado." << std::endl;
            }

        } else if (input == "FS") {
            cout << "Encerrando o Sistema de Locadora de Vídeos. Até logo!" << endl;
            break;
        } else {
            cout << "Comando inválido. Digite 'ajuda' para ver os comandos." << endl;
        }
    }

    return 0;
}
