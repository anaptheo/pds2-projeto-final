#include "cliente.hpp"
#include <algorithm>

Cliente::Cliente(string nome, string cpf) : _nome(nome), _cpf(cpf), _pontos_fidelidade(0){}

Cliente::~Cliente(){}

void Cliente::mostrarInfo(){
     cout << "Nome: " << this->_nome << endl;
     cout << "CPF: " << this->_cpf << endl;
     cout << "Pontos: " << this->_pontos_fidelidade << endl;
     //Filmes alugados
}

void Cliente::adicionarPontos(int pontos){
     this->_pontos_fidelidade += pontos;
     std::cout << "Total de pontos de fidelidade adquiridos nessa operação: " << pontos << std::endl; 
     std::cout << "Total de pontos de fidelidade acumulados: " << getPontos() << std::endl; 
}
void Cliente::zerarPontos(){
     this->_pontos_fidelidade = 0;
}
int Cliente::getPontos(){
     return(this->_pontos_fidelidade);
}

string Cliente::getNome(){
     return this->_nome;
}

string Cliente::getCpf(){
     return this->_cpf;
}

vector<Filme*>& Cliente::getFilmesAlugados(){
     return this->_filmes_alugados;
}

void Cliente::adicionarFilmeAlugado(Filme* filme) {
    _filmes_alugados.push_back(filme);
}

void Cliente::devolverFilmesAlugados() {
     _filmes_alugados.clear();
}