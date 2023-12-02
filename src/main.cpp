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

using namespace std;

/**
 * @brief Exibe os comandos disponíveis na interface da locadora.
 *
 * Esta função imprime no console os comandos disponíveis para interação
 * com o sistema da locadora.
 */

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

/**
 * @brief Função principal que inicia o programa da locadora.
 * @return Retorna 0 ao encerrar o programa.
 *
 * A função main é o ponto de entrada do programa. Nela, são declaradas variáveis
 * necessárias para a execução e exibida uma mensagem de boas-vindas ao usuário.
 * Em seguida, inicia um loop principal que aguarda comandos do usuário para
 * interagir com o sistema da locadora.
 */


int main() {

    // Declaração de variáveis
    string input;
    Locacao locacao;
    Categoria categoria;
    string cpf, codigo, titulo;
    int dias, quantidade;
    vector<Filme*> filmes;

    // Exibição de boas-vindas
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

    // Loop principal
    while (true) {

        /** @brief Solicita ao usuário que digite um comando.
         *
         * Este loop aguarda a entrada do usuário para interagir com o sistema da locadora.
         * Caso o usuário digite 'ajuda', exibe o menu de ajuda. Caso contrário, realiza
         * operações correspondentes ao comando inserido.
         */

        cout << "Digite um comando (digite 'ajuda' para os comandos): ";
        cin >> input;
        input = toUpperCase(input);
        try {
            
            /** @brief Processa os comandos do usuário.
             *
             * Este bloco de código dentro do try-catch processa os comandos inseridos pelo usuário.
             * Cada comando tem uma seção correspondente onde a ação apropriada é tomada.
             * Se o comando não for reconhecido, uma exceção é lançada.
             */

            if (input == "AJUDA") {
                /**
                 * @brief Exibe o menu de ajuda.
                 *
                 * Esta condição verifica se o comando inserido pelo usuário é 'AJUDA'
                 * e, se verdadeiro, chama a função displayHelp() para exibir o menu de ajuda.
                 */
                displayHelp();
            } else if (input == "CF") {
                /**
                 * @brief Cadastra um filme.
                 *
                 * Solicita informações ao usuário para cadastrar um filme. O usuário deve
                 * informar o tipo do filme (DVD, Bluray ou Fita) e fornece os detalhes específicos
                 * para cada tipo.
                 */
                string tipo;
                cout << "Digite o tipo do filme (D para DVD, B para Bluray, F para Fita): ";
                cin >> tipo;
                tipo = toUpperCase(tipo);

                Filme* filme;
                if (tipo == "D") {

                    /**
                     * @brief Cadastra um DVD.
                     *
                     * Se o tipo do filme for DVD, este bloco de código solicita informações
                     * específicas para DVDs, como código, título, quantidade e categoria.
                     * Após a coleta das informações, um objeto DVD é criado e cadastrado
                     * na locação.
                     */

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

                    // Cria um objeto DVD e cadastra na locação

                    filme = new DVD(titulo, codigo, quantidade, categoria);

                    locacao.cadastrarFilme(filme);

                } else if (tipo == "B") {

                     /**
                     * @brief Cadastra um Bluray.
                     *
                     * Se o tipo do filme for Bluray, este bloco de código solicita informações
                     * específicas para Blurays, como código, título e quantidade.
                     * Após a coleta das informações, um objeto Bluray é criado e cadastrado
                     * na locação.
                     */

                    cout << "Digite o codigo do Bluray: ";
                    cin >> codigo;

                    cout << "Digite o titulo do Bluray: ";
                    cin.ignore();
                    getline(cin, titulo);

                    cout << "Digite a quantidade de Blurays: ";
                    cin >> quantidade;

                    codigo = toLowerCase(codigo);
                    titulo = firstUpper(titulo);


                    // Cria um objeto Bluray e cadastra na locação
                    filme = new Bluray(titulo, codigo, quantidade);

                    locacao.cadastrarFilme(filme);


                } else if (tipo == "F") {

                    /**
                     * @brief Cadastra uma Fita.
                     *
                     * Se o tipo do filme for Fita, este bloco de código solicita informações
                     * específicas para Fitas, como código, título, quantidade e se a fita está rebobinada.
                     * Após a coleta das informações, um objeto Fita é criado e cadastrado
                     * na locação.
                     */

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

                    // Cria um objeto Fita e cadastra na locação

                    filme = new Fita(titulo, codigo, quantidade, rebobinada);

                    locacao.cadastrarFilme(filme);
                    
                } else {
                /**
                 * @brief Lança uma exceção para tipo de filme inválido.
                 *
                 * Se o tipo do filme não for DVD, Bluray ou Fita, uma exceção é lançada
                 * informando que o tipo de filme é inválido.
                 */

                    throw std::invalid_argument("ERRO: Tipo de filme inválido");
                }

                cout << "Filme cadastrado com sucesso!" << endl;

            } else if (input == "RF") {

                /**
                 * @brief Remove um filme do catálogo da locadora.
                 *
                 * Neste bloco de código, verifica-se se o comando inserido pelo usuário é 'RF'
                 * para remoção de filme. Se verdadeiro, solicita o código do filme a ser removido
                 * e chama o método `removerFilme` da instância `locacao` para realizar a remoção.
                 *
                 * @note A remoção é baseada no código do filme.
                 *
                 * @warning Caso o código fornecido não corresponda a nenhum filme no catálogo,
                 *          a função `removerFilme` pode lançar uma exceção.
                 *
                 * Exemplo de uso:
                 * @code
                 * // Digite 'RF' para remover um filme
                 * // O programa solicitará o código do filme a ser removido.
                 * @endcode
                 */

                string codigo;
                cout << "Digite o codigo do filme a ser removido: ";
                cin >> codigo; 

                // Chama o método para remover o filme com o código fornecido
                locacao.removerFilme(codigo);

            } else if (input == "LF") {

                /**
                 * @brief Lista os filmes disponíveis na locadora.
                 *
                 * Neste bloco de código, verifica-se se o comando inserido pelo usuário é 'LF'
                 * para listar os filmes disponíveis. Solicita ao usuário a preferência de ordenação
                 * dos filmes, seja por código ou por título, e chama o método apropriado na instância
                 * `locacao` para realizar a listagem.
                 *
                 * O usuário pode escolher a ordenação por código (C) ou por título (T).
                 *
                 * @note A ordenação é realizada internamente nos métodos `listarFilmesCodigo` e
                 *       `listarFilmesTitulo` da classe `Locacao`.
                 *
                 * @warning Caso o usuário forneça uma opção inválida, uma exceção é lançada,
                 *          indicando que a opção é inválida.
                 *
                 * Exemplo de uso:
                 * @code
                 * // Digite 'LF' para listar os filmes disponíveis.
                 * // O programa solicitará a preferência de ordenação (C para código, T para título).
                 * // Em seguida, exibirá a lista de filmes ordenada conforme a escolha.
                 * @endcode
                 */

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

            /** @brief Tratamento de exceção.
             *
             * Se ocorrer uma exceção durante o processamento dos comandos,
             * esta seção imprime a mensagem de erro no console.
             */

            cerr << e.what() << endl;
        }
    }

    return 0;
}