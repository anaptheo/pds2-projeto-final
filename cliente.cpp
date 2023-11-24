#include "cliente.hpp"

Cliente::Cliente(string nome, string cpf) : _nome(nome), _cpf(cpf), _pontos_fidelidade(0){}

Cliente::~Cliente(){}

void Cliente::MostrarInfo(){
     cout << "Nome: " << this->_nome << endl;
     cout << "CPF: " << this->_cpf << endl;
     cout << "Pontos: " << this->_pontos_fidelidade << endl;
     //Filmes alugados
}

void Cliente::AdicionarPontos(int pontos){
     this->_pontos_fidelidade += pontos;
}
void Cliente::ZerarPontos(){
     this->_pontos_fidelidade = 0;
}
int Cliente::RetornarPontos(){
     return(this->_pontos_fidelidade);
}

string Cliente::getNome(){
     return this->_nome;
}

string Cliente::getCpf(){
     return this->_cpf;
}

vector<Filme*> Cliente::getFilmesAlugados(){
     return this->_filmes_alugados;
}

void Cliente::adicionarFilmeAlugado(Filme* filme) {
    _filmes_alugados.push_back(filme);
}

void Cliente::devolverFilmeAlugado(Filme* filme) {
    auto it = find(_filmes_alugados.begin(), _filmes_alugados.end(), filme);
    
    if (it != _filmes_alugados.end()) {
        _filmes_alugados.erase(it);
          cout << "Filme devolvido com sucesso." << endl;
    } else {
          cout << "Erro: Filme não encontrado na lista de filmes alugados." << endl;
    }
}