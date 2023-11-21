#ifndef FITA_HPP
#define FITA_HPP

#include "filme.hpp"

class Fita : public Filme {
private:
    bool rebobinada;

public:
    // Construtor
    Fita(const std::string& titulo, int codigo, int quantidade, bool _rebobinada);

    // Métodos específicos para Fitas
    bool estaRebobinada() const;
    void rebobinar();

    // Método virtual da classe base
    double calcularValorLocacao(int dias) const override;
};

#endif // FITA_HPP
