#include <iostream>
#include <string>
#include <fstream>

#include "locacao.hpp"
#include "dvd.hpp"
#include "bluray.hpp"
#include "fita.hpp"

using namespace std;

void displayHelp() {
    cout << "Comandos disponiveis:" << endl;
    cout << "CF - Cadastrar Filme: Adiciona um filme ao catalogo da locadora." << endl;
    cout << "RF - Remover Filme: Remove um filme do catalogo da locadora." << endl;
    cout << "LF - Listar Filmes: Lista todos os filmes disponiveis na locadora." << endl;
    cout << "CC - Cadastrar Cliente: Adiciona um cliente a lista de clientes da locadora." << endl;
    cout << "RC - Remover Cliente: Remove um cliente da lista de clientes da locadora." << endl;
    cout << "LC - Listar Clientes: Lista todos os clientes cadastrados na locadora." << endl;
    cout << "AL - Alugar Filme: Permite alugar filmes para um cliente." << endl;
    cout << "DV - Devolver Filme: Devolve filmes alugados por um cliente." << endl;
    cout << "FS - Finalizar Sistema: Encerra o Sistema de Locadora de Videos." << endl;
    cout << "ajuda - Exibir este menu de ajuda." << endl;
}

int main() {
    string input;
    Locacao locacao;
    Categoria categoria;
    string cpf;
    string codigo;
    int dias;
    vector<Filme*> filmes;


    cout << "Bem-vindo ao Sistema de Locadora de Videos!" << endl;

    while (true) {
        cout << "Digite um comando (digite 'ajuda' para os comandos): ";
        cin >> input;
        try {
            if (input == "ajuda") {
                displayHelp();
            } else if (input == "CF") {
                char tipo;
                cout << "Digite o tipo do filme (D para DVD, B para Bluray, F para Fita): ";
                cin >> tipo;

                Filme* filme;
                if (tipo == 'D') {
                    string codigo;
                    int quantidade;
                    string titulo;

                    cout << "Digite o codigo do DVD: ";
                    cin >> codigo;

                    cout << "Digite o titulo do DVD: ";
                    cin.ignore();
                    getline(cin, titulo);

                    cout << "Digite a quantidade de DVDs: ";
                    cin >> quantidade;

                    cout << "Digite a categoria do DVD (L para Lancamento, E para Estoque, P para Promocao): ";
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
                            throw std::invalid_argument("ERRO: Categoria inválida");
                    }

                    filme = new DVD(titulo, codigo, quantidade, categoria);

                    locacao.cadastrarFilme(filme);

                } else if (tipo == 'B') {
                    string codigo; 
                    int quantidade;
                    string titulo;

                    cout << "Digite o codigo do Bluray: ";
                    cin >> codigo;

                    cout << "Digite o titulo do Bluray: ";
                    cin.ignore();
                    getline(cin, titulo);

                    cout << "Digite a quantidade de Blurays: ";
                    cin >> quantidade;

                    filme = new Bluray(titulo, codigo, quantidade);

                    locacao.cadastrarFilme(filme);

                } else if (tipo == 'F') {
                    string codigo; 
                    int quantidade;
                    string titulo;
                    bool rebobinada;

                    cout << "Digite o codigo da Fita: ";
                    cin >> codigo;

                    cout << "Digite o titulo da Fita: ";
                    cin.ignore();
                    getline(cin, titulo);

                    cout << "Digite a quantidade de Fitas: ";
                    cin >> quantidade;

                    cout << "A Fita esta rebobinada? (1 para Sim, 0 para Nao): "; // deveria ser aleatorio
                    cin >> rebobinada;

                    filme = new Fita(titulo, codigo, quantidade, rebobinada);

                    locacao.cadastrarFilme(filme);
                    
                } else {
                    throw std::invalid_argument("ERRO: Tipo de filme inválido");
                }

                cout << "Filme cadastrado com sucesso!" << endl;

            } else if (input == "RF") {
                string codigo;
                cout << "Digite o codigo do filme a ser removido: ";
                cin >> codigo; 
                locacao.removerFilme(codigo);

            } else if (input == "LF") {
                char escolha;
            cout << "Deseja listar os filmes por codigo ou por titulo? (C para codigo, T para titulo): ";
            cin >> escolha;
            if (escolha == 'C')
            {
                cout << "Listando filmes:" << endl;
                locacao.listarFilmesCodigo();
            } else if (escolha == 'T'){
                cout << "Listando filmes:" << endl;
                locacao.listarFilmesTitulo();
            } else{
                throw std::invalid_argument("ERRO: Opção inválida.");
            }

            } else if (input == "CC") {
                string nome, cpf;
                cout << "Digite o nome do cliente: ";
                cin.ignore();

                getline(cin, nome);
                cout << "Digite o CPF do cliente: ";
                cin >> cpf;

                locacao.cadastrarCliente(nome, cpf);

            } else if (input == "RC") {
                cout << "Digite o CPF do cliente a ser removido: ";
                string cpf;
                cin >> cpf;

                locacao.removerCliente(cpf);

            } else if (input == "LC") {
                cout << "Deseja listar os clientes por cpf ou por nome? (C para CPF, N para nome): ";
                
                char escolha;
                cin >> escolha;
                if (escolha == 'C') {
                    cout << "Listando clientes:" << endl;
                    locacao.listarClientesCodigo();
                } else if (escolha == 'N') {
                    cout << "Listando clientes:" << endl;
                    locacao.listarClientesNome();
                } else {
                    throw std::invalid_argument("ERRO: Opção inválida.");
                }

            } else if (input == "AL") {
                std::cout << "Digite o CPF do cliente: ";
                std::cin >> cpf;

                Cliente* cliente = locacao.getCliente(cpf);

                if (cliente != nullptr) {
                    // Permitir que o usuario insira multiplos codigos de filmes ate indicar que terminou
                    while (true) {
                        std::cout << "Digite o codigo do filme a ser alugado (ou -1 para encerrar): ";
                        std::cin >> codigo;

                        if (codigo == "-1") {
                            break; // Sair do loop se -1 for inserido
                        }

                        Filme* filme = locacao.getFilme(codigo);

                        if (filme != nullptr) {
                            filmes.push_back(filme);
                        } else {
                            std::string msg_erro = std::string("ERRO: Filme ") + codigo + std::string(" inexistente.");
                            throw std::runtime_error(msg_erro);
                        }
                    }

                    // Use locacao.alugarFilmes com o ponteiro Cliente obtido
                    locacao.alugarFilmes(cliente->getCpf(), filmes);

                    // Limpar o vetor de filmes apos o aluguel ser concluido
                    filmes.clear();
                } else {
                    throw std::invalid_argument("ERRO: Cliente não encontrado.");
                }

            } else if (input == "DV") {
                std::cout << "Digite o CPF do cliente que esta devolvendo os filmes: ";
                std::cin >> cpf;
                Cliente* cliente = locacao.getCliente(cpf);

                if (cliente->getFilmesAlugados().empty()) {
                    throw std::out_of_range("ERRO: Nenhum filme alugado para esse/essa cliente.");
                }

                if (cliente != nullptr) {
                    std::cout << "Digite a quantidade de dias do aluguel: ";
                    std::cin >> dias;
                    locacao.devolverFilmes(cliente, dias);
                } else {
                    throw std::invalid_argument("ERRO: Cliente nao encontrado.");
                }

            } else if (input == "FS") {
                cout << "Encerrando o Sistema de Locadora de Videos. Ate logo!" << endl; // sera q atrapalha a correcai?
                break;
            } else if (input == "LA") {
                string nome_arquivo;
                cin >> nome_arquivo;

                fstream arquivo;
                arquivo.open(nome_arquivo, ios::in);

                if (!arquivo) {
                    throw std::invalid_argument("ERRO: arquivo inexistente."); //mudar o tipo
                }
                else {
                    // chamar a nova funcao de cadastrar filme
                    arquivo.close(); 
                }
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