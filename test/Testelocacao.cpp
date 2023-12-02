#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "locacao.hpp"
#include "dvd.hpp"
#include "fita.hpp"
#include "bluray.hpp"
#include "cliente.hpp"

TEST_CASE("Testando gets"){
     Locacao locacao;
     Filme* filme1 = new DVD("filme1", "90", 10, Categoria::Estoque);
     Filme* filme2 = new DVD("filme2", "91", 10, Categoria::Estoque);
     Filme* filme3 = new DVD("filme3", "92", 10, Categoria::Estoque);
     Filme* filme4 = new DVD("filme4", "93", 10, Categoria::Estoque);
     Filme* filme5 = new DVD("filme5", "94", 10, Categoria::Estoque);
     locacao.cadastrarFilme(filme1);
     locacao.cadastrarFilme(filme2);
     locacao.cadastrarFilme(filme3);
     locacao.cadastrarFilme(filme4);
     locacao.cadastrarFilme(filme5);
     locacao.cadastrarCliente("Cliente1", "123456789");
     locacao.cadastrarCliente("Cliente2", "123456788");
     CHECK_EQ(locacao.getFilme("90"), filme1);
     CHECK_EQ(locacao.getFilme("91"), filme2);
     CHECK_EQ(locacao.getFilme("92"), filme3);
     CHECK_EQ(locacao.getFilme("93"), filme4);
     CHECK_EQ(locacao.getFilme("94"), filme5);
     CHECK_EQ(locacao.getCliente("123456789")->getNome(), "Cliente1");
     CHECK_EQ(locacao.getCliente("123456788")->getNome(), "Cliente2");
}





TEST_CASE("Testando vetor de filmes"){
     Locacao locacao;
     Filme* filme1 = new DVD("filme1", "90", 10, Categoria::Estoque);
     Filme* filme2 = new DVD("filme2", "91", 10, Categoria::Estoque);
     Filme* filme3 = new DVD("filme3", "92", 10, Categoria::Estoque);
     Filme* filme4 = new DVD("filme4", "93", 10, Categoria::Estoque);
     Filme* filme5 = new DVD("filme5", "94", 10, Categoria::Estoque);

     CHECK_EQ(locacao.getvectorFilmes().size(), 0);
     locacao.cadastrarFilme(filme1);
     locacao.cadastrarFilme(filme2);
     CHECK_EQ(locacao.getvectorFilmes().size(), 2);
     locacao.cadastrarFilme(filme3);
     locacao.cadastrarFilme(filme4);
     locacao.cadastrarFilme(filme5);
     CHECK_EQ(locacao.getvectorFilmes().size(), 5);
     locacao.removerFilme("90");
     CHECK_EQ(locacao.getvectorFilmes().size(), 4);
     locacao.removerFilme("91");
     locacao.removerFilme("92");
     locacao.removerFilme("93");
     locacao.removerFilme("94");
     CHECK_EQ(locacao.getvectorFilmes().size(), 0);
}

TEST_CASE("Testando vetor de clientes"){
     Locacao locacao;
     CHECK_EQ(locacao.getvectorClientes().size(), 0);
     locacao.cadastrarCliente("Cliente1", "123456789");
     locacao.cadastrarCliente("Cliente2", "123456788");
     CHECK_EQ(locacao.getvectorClientes().size(), 2);
     locacao.removerCliente("123456789");
     CHECK_EQ(locacao.getvectorClientes().size(), 1);
     locacao.removerCliente("123456788");
     CHECK_EQ(locacao.getvectorClientes().size(), 0);
}

TEST_CASE("Aluguel de filmes"){

}