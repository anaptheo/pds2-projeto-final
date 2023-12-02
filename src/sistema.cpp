/**
 * @file sistema.cpp
 * @brief Implementação dos métodos da classe Sistema.
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

/**
 * @brief Construtor da classe Sistema.
 * Inicializa o objeto de Locacao no construtor do Sistema.
 */
Sistema::Sistema(){
    _locacao;
}

/**
 * @brief Exibe o menu de ajuda com os comandos disponíveis.
 */
void Sistema::displayHelp() {
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
 * @brief Solicita informações e cadastra um novo cliente na locadora.
 * @throws std::invalid_argument se o CPF fornecido for inválido.
 */
void Sistema::cadastrarCliente() {
    string nome, cpf;
    cout << "Digite o nome do cliente: ";
    cin.ignore();
    getline(cin, nome);
    cout << "Digite o CPF do cliente: ";
    cin >> cpf;

    if (!all_of(cpf.begin(), cpf.end(), ::isdigit) || cpf.length() != 11) {
        throw invalid_argument("ERRO: CPF inválido. O CPF deve conter exatamente 11 dígitos numéricos.");
    }

    nome = firstUpper(nome);

    // Chama o método de cadastrarCliente da Locacao
    _locacao.cadastrarCliente(nome, cpf);
}

/**
 * @brief Solicita informações e aluga filmes para um cliente.
 * @throws std::invalid_argument se o cliente não for encontrado ou o código do filme for inexistente.
 */
void Sistema::alugarFilmes() {
    string nome, cpf, codigo;
    cout << "Digite o CPF do cliente: ";
    cin >> cpf;

    Cliente* cliente = _locacao.getCliente(cpf);

    if (cliente != nullptr) {
        // Permitir que o usuário insira múltiplos códigos de filmes até indicar que terminou
        vector<string> codigos_filmes;
        while (true) {
            std::cout << "Digite o código do filme a ser alugado (ou -1 para encerrar): ";
            std::cin >> codigo;

            if (codigo == "-1") {
                break; // Sair do loop se -1 for inserido
            }

            codigos_filmes.push_back(codigo);
        }

        vector<Filme*> filmes_a_alugar;
        // Varre o vetor de códigos de filmes
        for (const auto& codigo : codigos_filmes) {
            Filme* filme_alugado = _locacao.getFilme(codigo);

            if (filme_alugado != nullptr) {
                filmes_a_alugar.push_back(filme_alugado);

                // Se tiver algum filme do tipo BluRay ele pergunta sobre o player
                if (filme_alugado->getTipo() == Filme::Tipo::BluRay) {
                    Bluray* bluray_alugado = dynamic_cast<Bluray*>(filme_alugado);
                    string querAparelho;
                    cout << "Você quer alugar o player BluRay com seu filme? (S = Sim / N = não)" << endl;
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
        
        // Usa _locacao.alugarFilmes com o ponteiro Cliente obtido
        _locacao.alugarFilmes(cliente->getCpf(), filmes_a_alugar);

        // Limpar o vetor de filmes após o aluguel ser concluído
        filmes_a_alugar.clear();

    } else {
        throw std::invalid_argument("ERRO: Cliente não encontrado.");
    }
}

/**
 * @brief Solicita informações e cadastra um novo filme na locadora.
 * @throws std::invalid_argument se o tipo de filme for inválido.
 */
void Sistema::cadastrarFilme(){
    string cpf, codigo, titulo, tipo;
    int dias, quantidade;
    Categoria categoria;

    cout << "Digite o tipo do filme (D para DVD, B para Bluray, F para Fita): ";
    cin >> tipo;
    tipo = toUpperCase(tipo);

    Filme* filme;
    if (tipo == "D") {
        cout << "Digite o código do DVD: ";
        cin >> codigo;
        
        cout << "Digite o título do DVD: ";
        cin.ignore();
        getline(cin, titulo);
        
        cout << "Digite a quantidade de DVDs: ";
        cin >> quantidade;
        
        cout << "Digite a categoria do DVD (L para Lançamento, E para Estoque, P para Promoção): ";
        string categoriaDVD;
        cin >> categoriaDVD;
        categoriaDVD = toUpperCase(categoriaDVD);
        char categoriaChar = categoriaDVD[0];

        // Converte a letra da categoria para o enum correspondente
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
        }

        codigo = toLowerCase(codigo);
        titulo = firstUpper(titulo);

        // Cria um novo objeto DVD
        filme = new DVD(titulo, codigo, quantidade, categoria);

        // Chama o método de cadastrarFilme da Locacao
        _locacao.cadastrarFilme(filme);
    } else if (tipo == "B") {
        cout << "Digite o código do Bluray: ";
        cin >> codigo;

        cout << "Digite o título do Bluray: ";
        cin.ignore();
        getline(cin, titulo);

        cout << "Digite a quantidade de Blurays: ";
        cin >> quantidade;

        codigo = toLowerCase(codigo);
        titulo = firstUpper(titulo);

        // Cria um novo objeto Bluray
        filme = new Bluray(titulo, codigo, quantidade);

        // Chama o método de cadastrarFilme da Locacao
        _locacao.cadastrarFilme(filme);
    } else if (tipo == "F") {
        bool rebobinada;

        cout << "Digite o código da Fita: ";
        cin >> codigo;

        cout << "Digite o título da Fita: ";
        cin.ignore();
        getline(cin, titulo);

        cout << "Digite a quantidade de Fitas: ";
        cin >> quantidade;

        cout << "A Fita está rebobinada? (1 para Sim, 0 para Não): ";
        cin >> rebobinada;

        codigo = toLowerCase(codigo);
        titulo = firstUpper(titulo);

        // Cria um novo objeto Fita
        filme = new Fita(titulo, codigo, quantidade, rebobinada);

        // Chama o método de cadastrarFilme da Locacao
        _locacao.cadastrarFilme(filme);
        
    } else {
        throw std::invalid_argument("ERRO: Tipo de filme inválido");
    }

    cout << "Filme cadastrado com sucesso!" << endl;
}

/**
 * @brief Remove um cliente da locadora com base no CPF.
 * @throws std::out_of_range se nenhum filme estiver alugado para o cliente.
 */
void Sistema::removerCliente() {
    cout << "Digite o CPF do cliente a ser removido: ";
    string cpf;
    cin >> cpf;

    _locacao.removerCliente(cpf);
}

/**
 * @brief Remove um filme da locadora com base no código.
 */
void Sistema::removerFilme() {
    string codigo;
    cout << "Digite o código do filme a ser removido: ";
    cin >> codigo; 
    _locacao.removerFilme(codigo);
}

/**
 * @brief Permite que um cliente devolva filmes alugados.
 * @throws std::out_of_range se nenhum filme estiver alugado para o cliente.
 * @throws std::invalid_argument se o cliente não for encontrado.
 */
void Sistema::devolverFilmes() {
    string cpf;
    int dias;

    std::cout << "Digite o CPF do cliente que está devolvendo os filmes: ";
    std::cin >> cpf;
    Cliente* cliente = _locacao.getCliente(cpf);

    if (cliente->getFilmesAlugados().empty()) {
        throw std::out_of_range("ERRO: Nenhum filme alugado para esse cliente.");
    }

    if (cliente != nullptr) {
        std::cout << "Digite a quantidade de dias do aluguel: ";
        std::cin >> dias;
        _locacao.devolverFilmes(cliente, dias);
    } else {
        throw std::invalid_argument("ERRO: Cliente não encontrado.");
    }
}

/**
 * @brief Lista os filmes disponíveis na locadora por código ou título.
 * @throws std::invalid_argument se a opção de listagem for inválida.
 */
void Sistema::listarFilmes() {
    string escolha;
    cout << "Deseja listar os filmes por código ou por título? (C para código, T para título): ";
    cin >> escolha;
    escolha = toUpperCase(escolha);

    if (escolha == "C"){
        cout << "Listando filmes:" << endl;
        _locacao.listarFilmesCodigo();
    } else if (escolha == "T"){
        cout << "Listando filmes:" << endl;
        _locacao.listarFilmesTitulo();
    } else{
        throw std::invalid_argument("ERRO: Opção inválida.");
    }
}

/**
 * @brief Lista os clientes cadastrados na locadora por CPF ou nome.
 * @throws std::invalid_argument se a opção de listagem for inválida.
 */
void Sistema::listarClientes() {
     cout << "Deseja listar os clientes por CPF ou por nome? (C para CPF, N para nome): ";
                
    string escolha;
    cin >> escolha;
    escolha = toUpperCase(escolha);

    if (escolha == "C") {
        cout << "Listando clientes:" << endl;
        _locacao.listarClientesCodigo();
    } else if (escolha == "N") {
        cout << "Listando clientes:" << endl;
        _locacao.listarClientesNome();
    } else {
        throw std::invalid_argument("ERRO: Opção inválida.");
    }
}

/**
 * @brief Lê informações de um arquivo e cadastra os filmes na locadora.
 * @throws std::invalid_argument se o arquivo não existir.
 */
void Sistema::lerArquivo() {
    string nome_arquivo;
    cin >> nome_arquivo;

    fstream arquivo;
    arquivo.open(nome_arquivo, ios::in);

    if (!arquivo) {
        throw std::invalid_argument("ERRO: Arquivo inexistente.");
    }
    else {
        // chamar a nova função de cadastrar filme
        arquivo.close(); 
    }
}