#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "dvd.hpp"
#include "fita.hpp"
#include "bluray.hpp"

TEST_CASE("Testando Getters") {
     DVD dvd("O Poderoso Chefão", "90", 10, Categoria::Lancamento);
     CHECK_EQ(dvd.getTitulo(), "O Poderoso Chefão");
     CHECK_EQ(dvd.getCodigo(), "90");
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 10);
     //CHECK_EQ(dvd.getTipo(), Categoria::Lancamento);
     DVD dvd2("O Poderoso Chefão 2", "91", 7, Categoria::Lancamento);
     CHECK_EQ(dvd2.getTitulo(), "O Poderoso Chefão 2");
     CHECK_EQ(dvd2.getCodigo(), "91");
     CHECK_EQ(dvd2.getUnidadesDisponiveis(), 7);
     //CHECK_EQ(dvd2.getTipo(), Categoria::Lancamento);
}
TEST_CASE("Testando unidades disponiveis") {
     DVD dvd("Forest Gump", "90", 10, Categoria::Lancamento);
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 10);
     dvd.adicionarUnidadesDisponiveis(5);
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 15);
     dvd.removerUnidadeDisponivel();
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 14);
     dvd.removerUnidadeDisponivel();
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 13);
     dvd.removerUnidadeDisponivel();
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 12);
     dvd.removerUnidadeDisponivel();
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 11);
     dvd.removerUnidadeDisponivel();
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 10);
     dvd.removerUnidadeDisponivel();
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 9);
     dvd.removerUnidadeDisponivel();
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 8);
     dvd.removerUnidadeDisponivel();
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 7);
     dvd.removerUnidadeDisponivel();
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 6);
     dvd.removerUnidadeDisponivel();
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 5);
     dvd.removerUnidadeDisponivel();
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 4);
     dvd.removerUnidadeDisponivel();
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 3);
     dvd.removerUnidadeDisponivel();
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 2);
     dvd.removerUnidadeDisponivel();
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 1);
     dvd.removerUnidadeDisponivel();
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 0);
     dvd.adicionarUnidadesDisponiveis(5);
     CHECK_EQ(dvd.getUnidadesDisponiveis(), 5);
}

TEST_CASE("Testando classe dvd"){
     DVD dvd("O Poderoso Chefão", "90", 10, Categoria::Lancamento);
     CHECK_EQ(dvd.calcularValorLocacao(2), 40);
     CHECK_EQ(dvd.calcularValorLocacao(3), 60);
     CHECK_EQ(dvd.calcularValorLocacao(4), 80);
     CHECK_EQ(dvd.calcularValorLocacao(5), 100);
     CHECK_EQ(dvd.calcularValorLocacao(100), 2000);
     DVD dvd2("Pulp Fiction", "91", 7, Categoria::Estoque);
     CHECK_EQ(dvd2.calcularValorLocacao(2), 20);
     CHECK_EQ(dvd2.calcularValorLocacao(3), 30);
     CHECK_EQ(dvd2.calcularValorLocacao(4), 40);
     CHECK_EQ(dvd2.calcularValorLocacao(5), 50);
     CHECK_EQ(dvd2.calcularValorLocacao(100), 1000);
     DVD dvd3("Batman, O Cavaleiro das Trevas retorna", "92", 7, Categoria::Promocao);
     CHECK_EQ(dvd3.calcularValorLocacao(2), 10);
     CHECK_EQ(dvd3.calcularValorLocacao(3), 10);
     CHECK_EQ(dvd3.calcularValorLocacao(4), 10);
     CHECK_EQ(dvd3.calcularValorLocacao(5), 10);
     CHECK_EQ(dvd3.calcularValorLocacao(100), 10);
}

TEST_CASE("Testando classe fita"){
     Fita fita("Xuxa para baixinhos", "93", 10, true);
     CHECK_EQ(fita.calcularValorLocacao(2), 10);
     CHECK_EQ(fita.calcularValorLocacao(3), 15);
     CHECK_EQ(fita.calcularValorLocacao(4), 20);
     CHECK_EQ(fita.calcularValorLocacao(5), 25);
     CHECK_EQ(fita.calcularValorLocacao(100), 500);
     Fita fita2("Xuxa para baixinhos 2", "94", 7, false);
     CHECK_EQ(fita2.calcularValorLocacao(2), 12);
     CHECK_EQ(fita2.calcularValorLocacao(3), 17);
     CHECK_EQ(fita2.calcularValorLocacao(4), 22);
     CHECK_EQ(fita2.calcularValorLocacao(5), 27);
     CHECK_EQ(fita2.calcularValorLocacao(100), 502);

     CHECK_EQ(fita2.estaRebobinada(), false);
     fita2.rebobinar();
     CHECK_EQ(fita2.estaRebobinada(), true);

     CHECK_EQ(fita.estaRebobinada(), true);
     fita.rebobinar();
     CHECK_EQ(fita.estaRebobinada(), true);
}

TEST_CASE("Testando classe bluray"){
     Bluray bluray("O poderoso chefinho", "95", 10);
     CHECK_EQ(bluray.calcularValorLocacao(2), 50);
     CHECK_EQ(bluray.calcularValorLocacao(3), 75);
     CHECK_EQ(bluray.calcularValorLocacao(4), 100);
     CHECK_EQ(bluray.calcularValorLocacao(5), 125);
     CHECK_EQ(bluray.calcularValorLocacao(100), 2500);

     bluray.setQuantidadeAparelhos(10);
     CHECK_EQ(bluray.getQuantidadeAparelhosDisponiveis(), 10);
}
