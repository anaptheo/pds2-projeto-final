#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "filme.hpp"
#include "doctest.h"
#include "dvd.hpp"
#include "cliente.hpp"


TEST_CASE("Testando Getters") {
     Cliente cliente("Joao", "12345678910");
     CHECK_EQ(cliente.getCpf(), "12345678910");
     CHECK_EQ(cliente.getNome(), "Joao");
     CHECK_EQ(cliente.getPontos(), 0);
     Cliente cliente2("Maria", "12345678910");
     CHECK_EQ(cliente2.getCpf(), "12345678910");
     CHECK_EQ(cliente2.getNome(), "Maria");
     CHECK_EQ(cliente2.getPontos(), 0);
}

TEST_CASE("Testando sistema de pontos") {
     Cliente cliente("Joao", "12345678910");
     CHECK_EQ(cliente.getPontos(), 0);
     cliente.adicionarPontos(10);
     CHECK_EQ(cliente.getPontos(), 10);
     cliente.adicionarPontos(20);
     CHECK_EQ(cliente.getPontos(), 30);
     cliente.zerarPontos();
     CHECK_EQ(cliente.getPontos(), 0);
     cliente.adicionarPontos(10);
     CHECK_EQ(cliente.getPontos(), 10);
     cliente.adicionarPontos(20);
     CHECK_EQ(cliente.getPontos(), 30);
}

TEST_CASE("Testando vetor de filmes"){
     DVD dvd("O Poderoso Chefão", "90", 10, Categoria::Lancamento);
     DVD dvd2("O Poderoso Chefão 2", "91", 7, Categoria::Lancamento);
     Cliente cliente("Joao", "12345678910");
     cliente.adicionarFilmeAlugado(&dvd); 
     CHECK_EQ(cliente.getFilmesAlugados().size(), 1);
     cliente.adicionarFilmeAlugado(&dvd2);
     CHECK_EQ(cliente.getFilmesAlugados().size(), 2);
     cliente.devolverFilmesAlugados();
     CHECK_EQ(cliente.getFilmesAlugados().size(), 0);
     
}
