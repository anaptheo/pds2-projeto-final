#ifndef FILME_HPP
#define FILME_HPP

#include <iostream>
#include <string>

class Filme {
private:
    std::string titulo;
    int codigo;
    int quantidade; 
    int unidadesDisponiveis;
    std::string tipo;

public:
    // Construtor
    Filme(const std::string& titulo, int codigo, int quantidade, const std::string& tipo);

    // Destrutor
    ~Filme();

    // Getters
    const std::string& getTitulo() const;
    int getCodigo() const;
    int getUnidadesDisponiveis() const;
    const std::string& getTipo() const;

    // Metodos da classe
    void incrementarUnidades();
    void decrementarUnidades();
    virtual double calcularValorLocacao(int dias) const = 0;

};

#endif // FILME_HPP
