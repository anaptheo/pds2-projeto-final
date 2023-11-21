#ifndef BLURAY_HPP
#define BLURAY_HPP

#include "filme.hpp"

class Bluray : public Filme {
private:
    static int quantidadeAparelhos; // Variável estática compartilhada entre todos os objetos Bluray
    bool playerAlugado; // Atributo para rastrear se um player foi alugado junto com o filme

public:
    // Construtor
    Bluray(const std::string& titulo, int codigo, int quantidade);

    // Métodos específicos para Blu-rays
    static int getQuantidadeAparelhosDisponiveis();
    static void setQuantidadeAparelhos(int quantidade);
    void alugarAparelho();
    void devolverAparelho();

    // Método virtual da classe base
    double calcularValorLocacao(int dias) const override;
};

#endif // BLURAY_HPP
