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


Sistema::Sistema(){
    _locacao;
}

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

void Sistema::cadastrarCliente() {
    string nome, cpf;
    cout << "Digite o nome do cliente: ";
    cin.ignore();

    getline(cin, nome);
    cout << "Digite o CPF do cliente: ";
    cin >> cpf;

    if (!all_of(cpf.begin(), cpf.end(), ::isdigit) || cpf.length() != 11) {
    throw invalid_argument("ERRO: CPF invalido. O CPF deve conter exatamente 11 digitos numericos.");
    }

    nome = firstUpper(nome);

    _locacao.cadastrarCliente(nome, cpf);
}

void Sistema::alugarFilmes() {
    string nome, cpf, codigo;
    cout << "Digite o CPF do cliente: ";
    cin >> cpf;

    Cliente* cliente = _locacao.getCliente(cpf);

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

        vector<Filme*> filmes_a_alugar;
        // Varre o vetor de códigos de filmes
        for (const auto& codigo : codigos_filmes) {
            Filme* filme_alugado = _locacao.getFilme(codigo);

            if (filme_alugado != nullptr) {
                filmes_a_alugar.push_back(filme_alugado);

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
        
        // Use _locacao.alugarFilmes com o ponteiro Cliente obtido
        _locacao.alugarFilmes(cliente->getCpf(), filmes_a_alugar);

        // Limpar o vetor de filmes apos o aluguel ser concluido
        filmes_a_alugar.clear();

    } else {
        throw std::invalid_argument("ERRO: Cliente não encontrado.");
    }
}

void Sistema::cadastrarFilme(){
    string cpf, codigo, titulo, tipo;
    int dias, quantidade;
    Categoria categoria;

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
        }

        codigo = toLowerCase(codigo);
        titulo = firstUpper(titulo);

        filme = new DVD(titulo, codigo, quantidade, categoria);

        _locacao.cadastrarFilme(filme);
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

        _locacao.cadastrarFilme(filme);
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

        _locacao.cadastrarFilme(filme);
        
    } else {
        throw std::invalid_argument("ERRO: Tipo de filme inválido");
    }

    cout << "Filme cadastrado com sucesso!" << endl;
}

void Sistema::removerCliente() {
    cout << "Digite o CPF do cliente a ser removido: ";
    string cpf;
    cin >> cpf;

    _locacao.removerCliente(cpf);
}

void Sistema::removerFilme() {
    string codigo;
    cout << "Digite o codigo do filme a ser removido: ";
    cin >> codigo; 
    _locacao.removerFilme(codigo);
}

void Sistema::devolverFilmes() {
    string cpf;
    int dias;

    std::cout << "Digite o CPF do cliente que esta devolvendo os filmes: ";
    std::cin >> cpf;
    Cliente* cliente = _locacao.getCliente(cpf);

    if (cliente->getFilmesAlugados().empty()) {
        throw std::out_of_range("ERRO: Nenhum filme alugado para esse/essa cliente.");
    }

    if (cliente != nullptr) {
        std::cout << "Digite a quantidade de dias do aluguel: ";
        std::cin >> dias;
        _locacao.devolverFilmes(cliente, dias);
    } else {
        throw std::invalid_argument("ERRO: Cliente nao encontrado.");
    }

}

void Sistema::listarFilmes() {
    string escolha;
    cout << "Deseja listar os filmes por codigo ou por titulo? (C para codigo, T para titulo): ";
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

void Sistema::listarClientes() {
     cout << "Deseja listar os clientes por cpf ou por nome? (C para CPF, N para nome): ";
                
    string escolha;
    cin >> escolha;
    escolha = toUpperCase(escolha);

    if (escolha == "C") {
        cout << "Listando clientes:" << endl;
        _locacao.listarClientesCodigo();
    } else if (escolha == "C") {
        cout << "Listando clientes:" << endl;
        _locacao.listarClientesNome();
    } else {
        throw std::invalid_argument("ERRO: Opção inválida.");
    }
}

void Sistema::lerArquivo() {
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
}

