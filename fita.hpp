#ifndef FITA_HPP
#define FITA_HPP

#include "filme.hpp"

class Fita : public Filme {
private:
    bool rebobinada;

public:
    Fita(const std::string& titulo, int codigo, int quantidade, bool _rebobinada);

    bool estaRebobinada() const;
    void rebobinar();

    double calcularValorLocacao(int dias) const override;
};

#endif // FITA_HPP
