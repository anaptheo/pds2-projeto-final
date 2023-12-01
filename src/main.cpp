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

std::string toLowerCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){ return std::tolower(c); });
    return result;
}

std::string toUpperCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){ return std::toupper(c); });
    return result;
}

std::string firstUpper(const std::string& input) {
    std::string result = input;
    bool capitalizeNext = true;
    for (char& c : result) {
        if (std::isalpha(c)) {
            if (capitalizeNext) {
                c = std::toupper(c);
                capitalizeNext = false;
            } else {
                c = std::tolower(c);
            }
        } else {
            capitalizeNext = true;
        }
    }
    return result;
}

int main() {
    string input;
    Locacao locacao;
    Categoria categoria;
    string cpf, codigo, titulo;
    int dias, quantidade;
    vector<Filme*> filmes;

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
                displayHelp();
            } else if (input == "CF") {
                string tipo;
                cout << "Digite o tipo do filme (D para DVD, B para Bluray, F para Fita): ";
                cin >> tipo;
                tipo = toUpperCase(tipo);

                Filme* filme;
                if (tipo == "D") {

                   cout << "Digite o codigo do DVD: ";
                    cin >> codigo;
                    cout << "Digite o titulo do DVD: ";
                    cin.ignore();
                    getline(cin, titulo);
                    cout << "Digite a quantidade de DVDs: ";
                    cin >> quantidade;
                    cout << "Digite a categoria do DVD (L para Lancamento, E para Estoque, P para Promocao): ";
                    
                    string categoriaDVD;
                    cin >> categoriaDVD;
                    categoriaDVD = toUpperCase(categoriaDVD);
                    char categoriaChar = categoriaDVD[0];

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
                            cout << "Categoria invalida." << endl;
                            continue;
                    }

                    codigo = toLowerCase(codigo);
                    titulo = firstUpper(titulo);

                    filme = new DVD(titulo, codigo, quantidade, categoria);

                    locacao.cadastrarFilme(filme);

                } else if (tipo == "B") {
                    cout << "Digite o codigo do Bluray: ";
                    cin >> codigo;

                    cout << "Digite o titulo do Bluray: ";
                    cin.ignore();
                    getline(cin, titulo);

                    cout << "Digite a quantidade de Blurays: ";
                    cin >> quantidade;

                    codigo = toLowerCase(codigo);
                    titulo = firstUpper(titulo);

                    filme = new Bluray(titulo, codigo, quantidade);

                    locacao.cadastrarFilme(filme);


                } else if (tipo == "F") {
                    bool rebobinada;

                    cout << "Digite o codigo da Fita: ";
                    cin >> codigo;
                    cout << "Digite o titulo da Fita: ";
                    cin.ignore();
                    getline(cin, titulo);
                    cout << "Digite a quantidade de Fitas: ";
                    cin >> quantidade;
                    cout << "A Fita esta rebobinada? (1 para Sim, 0 para Nao): ";
                    cin >> rebobinada;

                    codigo = toLowerCase(codigo);
                    titulo = firstUpper(titulo);

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
                string escolha;
                cout << "Deseja listar os filmes por codigo ou por titulo? (C para codigo, T para titulo): ";
                cin >> escolha;
                escolha = toUpperCase(escolha);

                if (escolha == "C"){
                    cout << "Listando filmes:" << endl;
                    locacao.listarFilmesCodigo();
                } else if (escolha == "T"){
                    cout << "Listando filmes:" << endl;
                    locacao.listarFilmesTitulo();
                } else{
                    throw std::invalid_argument("ERRO: Opção inválida.");
                }

            } else if (input == "CC") {
                string nome;
                cout << "Digite o nome do cliente: ";
                cin.ignore();

                getline(cin, nome);
                cout << "Digite o CPF do cliente: ";
                cin >> cpf;

                if (!all_of(cpf.begin(), cpf.end(), ::isdigit) || cpf.length() != 11) {
                throw invalid_argument("ERRO: CPF invalido. O CPF deve conter exatamente 11 digitos numericos.");
                }

                nome = firstUpper(nome);

                locacao.cadastrarCliente(nome, cpf);

            } else if (input == "RC") {
                cout << "Digite o CPF do cliente a ser removido: ";
                string cpf;
                cin >> cpf;

                locacao.removerCliente(cpf);

            } else if (input == "LC") {
                cout << "Deseja listar os clientes por cpf ou por nome? (C para CPF, N para nome): ";
                
                string escolha;
                cin >> escolha;
                escolha = toUpperCase(escolha);

                if (escolha == "C") {
                    cout << "Listando clientes:" << endl;
                    locacao.listarClientesCodigo();
                } else if (escolha == "C") {
                    cout << "Listando clientes:" << endl;
                    locacao.listarClientesNome();
                } else {
                    throw std::invalid_argument("ERRO: Opção inválida.");
                }

            } else if (input == "AL") {
                cout << "Digite o CPF do cliente: ";
                cin >> cpf;

                Cliente* cliente = locacao.getCliente(cpf);

                if (cliente != nullptr) {
                   // Permitir que o usuário insira múltiplos códigos de filmes até indicar que terminou
                    vector<string> codigos_filmes;
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
                        
                        codigos_filmes.push_back(codigo);
                    }

                    // Varre o vetor de códigos de filmes
                    for (const auto& codigo : codigos_filmes) {
                        Filme* filme_alugado = locacao.getFilme(codigo);

                        if (filme_alugado != nullptr) {
                            cliente->adicionarFilmeAlugado(filme_alugado);

                            // Se tiver algum filme do tipo BluRay ele pergunta do player
                            if (filme_alugado->getTipo() == Filme::Tipo::BluRay) {
                                Bluray* bluray_alugado = dynamic_cast<Bluray*>(filme_alugado);
                                string querAparelho;
                                cout << "Voce quer alugar o player BluRay com seu filme? (S = Sim / N = nao)" << endl;
                                cin >> querAparelho;
                                querAparelho = toUpperCase(querAparelho);

                                if (querAparelho == "S") {
                                    bluray_alugado->alugarAparelho();
                                }
                            }
                        } else {
                            throw invalid_argument("ERRO: Filme com código inexistente");
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
                cout << "\n===================================" << endl;
                cout << "   Obrigado por utilizar a Locadora PDS!" << endl;
                cout << "    Esperamos te ver novamente em breve." << endl;
                cout << "        Tenha um otimo dia!" << endl;
                cout << "===================================\n" << endl;

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