#include <iostream>
#include <tuple>
#include <string>
#include <fstream>
#include <deque>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string>
#include "locacao.hpp"
#include "dvd.hpp"
#include "bluray.hpp"
#include "fita.hpp"
#include "formatacao.hpp"
#include "sistema.hpp"


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

void Sistema::cadastrarCliente(std::deque<std::string> input_list) {
    string nome, cpf;
    cpf = input_list[0];
    input_list.pop_front();

    if (!all_of(cpf.begin(), cpf.end(), ::isdigit) || cpf.length() != 11) {
        throw invalid_argument("ERRO: CPF invalido. O CPF deve conter exatamente 11 digitos numericos.");
    }

    nome = retornaStringFormatada(input_list);
    _locacao.cadastrarCliente(nome, cpf);
}

void Sistema::alugarFilmes(std::deque<std::string> input_list) {
    string cpf;
    cpf = input_list[0];
    input_list.pop_front();
    
    bool quer_aparelho_bluray = false;
    if (toUpperCase(input_list[0]) == "ALUGAR_APARELHO"){
        quer_aparelho_bluray = true;
        input_list.pop_front();
    }

    Cliente* cliente = _locacao.getCliente(cpf);

    if (cliente != nullptr) {
        deque<string> codigos_filmes = input_list;
        vector<Filme*> filmes_a_alugar;
        // Varre o vetor de códigos de filmes
        for (const auto& codigo : codigos_filmes) {
            Filme* filme_alugado = _locacao.getFilme(codigo);

            if (filme_alugado != nullptr) {
                filmes_a_alugar.push_back(filme_alugado);

                // // Se tiver algum filme do tipo BluRay ele pergunta do player
                bool tem_aparelho_alugado = cliente->getAparelhoAlugado();
                if (filme_alugado->getTipo() == Filme::Tipo::BluRay && quer_aparelho_bluray && !tem_aparelho_alugado) {
                    Bluray* bluray_alugado = dynamic_cast<Bluray*>(filme_alugado);
                    bluray_alugado->alugarAparelho();
                    cliente->alugarAparelhoBluray();
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

void Sistema::cadastrarFilme(std::deque<std::string> input_list){
    string codigo, titulo, tipo;
    int quantidade;
    Categoria categoria;

    tipo = toUpperCase(input_list[0]);
    input_list.pop_front();

    quantidade = stoi(input_list[0]);
    input_list.pop_front();

    codigo = toLowerCase(input_list[0]);
    input_list.pop_front();

    Filme* filme;
    if (tipo == "D") {
        string categoriaDVD;
        categoriaDVD = toUpperCase(input_list[0]);
        input_list.pop_front();

        switch (char(categoriaDVD[0])) {
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
                std::cout << "Categoria invalida." << endl;
        }
        titulo = retornaStringFormatada(input_list);
        filme = new DVD(titulo, codigo, quantidade, categoria);
    } else if (tipo == "B") {
        titulo = retornaStringFormatada(input_list);
        filme = new Bluray(titulo, codigo, quantidade);
    } else if (tipo == "F") {
        bool rebobinada = true;

        titulo = retornaStringFormatada(input_list);
        filme = new Fita(titulo, codigo, quantidade, rebobinada);
    } else {
        throw std::invalid_argument("ERRO: Tipo de filme inválido");
    }

    _locacao.cadastrarFilme(filme);
    cout << "Filme cadastrado com sucesso!" << endl;
}

void Sistema::removerCliente(std::deque<std::string> input_list) {
    string cpf = input_list[0];
    _locacao.removerCliente(cpf);
}

void Sistema::removerFilme(std::deque<std::string> input_list) {
    string codigo = input_list[0];
    _locacao.removerFilme(codigo);
}

void Sistema::devolverFilmes(std::deque<std::string> input_list) {
    string cpf = input_list[0]; // adicionar verificacao de cpf aqui
    Cliente* cliente = _locacao.getCliente(cpf);

    if (cliente->getFilmesAlugados().empty()) {
        throw std::out_of_range("ERRO: Nenhum filme alugado para esse/essa cliente.");
    }

    if (cliente != nullptr) {
        int dias = stoi(input_list[1]); 
        _locacao.devolverFilmes(cliente, dias);
    } else {
        throw std::invalid_argument("ERRO: Cliente nao encontrado.");
    }

}

void Sistema::listarFilmes(std::deque<std::string> input_list) {
    string escolha = input_list[0];
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

void Sistema::listarClientes(std::deque<std::string> input_list) {
    string escolha = input_list[0];
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

void Sistema::lerArquivo(string nome_arquivo) {
    std::ifstream arquivo(nome_arquivo);
    if (arquivo.is_open()) {
        std::string linha;
        while (std::getline(arquivo, linha)) {
            std::deque<std::string> lista_input;
            string comando;
            tie(comando, lista_input) = processaInput(linha);
            controlaComando(comando, lista_input);
        }
        arquivo.close();
    } else {
        throw std::invalid_argument("ERRO: arquivo inexistente.");
    }
}

std::tuple<std::string, std::deque<std::string>> Sistema::processaInput(std::string input) {
    std::string str(input);
    std::istringstream split(str);

    std::deque<std::string> lista_input;
    char split_char = ' ';
    for (std::string each; std::getline(split, each, split_char); lista_input.push_back(each));
    
    string comando = lista_input[0];
    lista_input.pop_front();
    
    return std::make_tuple(comando, lista_input);
}

bool Sistema::controlaComando(string comando, std::deque<std::string> lista_input) {
    try {
        if (comando == "AJUDA") {
            displayHelp();
        } else if (comando == "CF") {
            cadastrarFilme(lista_input);
        } else if (comando == "RF") {
            removerFilme(lista_input);
        } else if (comando == "LF") {
            listarFilmes(lista_input);
        } else if (comando == "CC") {
            cadastrarCliente(lista_input);
        } else if (comando == "RC") {
            removerCliente(lista_input);
        } else if (comando == "LC") {
            listarClientes(lista_input);
        } else if (comando == "AL") {
            alugarFilmes(lista_input);
        } else if (comando == "DV") {
            devolverFilmes(lista_input);
        } else if (comando == "FS") {
            cout << "\n===================================" << endl;
            cout << "   Obrigado por utilizar a Locadora PDS!" << endl;
            cout << "    Esperamos te ver novamente em breve." << endl;
            cout << "        Tenha um otimo dia!" << endl;
            cout << "===================================\n" << endl;

            return true;
        } else if (comando == "LA") {
            lerArquivo(lista_input[0]);
        } else {
            throw std::invalid_argument("ERRO: Comando invalido. Digite 'ajuda' para ver os comandos.");
        }
    } catch (std::exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
} 