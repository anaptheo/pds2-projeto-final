#ifndef DVD_HPP
#define DVD_HPP

#include "filme.hpp"

class DVD : public Filme {
protected:
    enum class Tipo { Lancamento, Estoque, Promocao };
    Tipo tipo;

public:
    DVD(const std::string& titulo, int codigo, int quantidade, Tipo _tipo);

    double calcularValorLocacao(int dias) const override;

  
};

#endif // DVD_HPP
