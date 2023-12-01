#ifndef FILME_HPP
#define FILME_HPP

#include <iostream>
#include <string>

class Filme {
public:
    enum class Tipo {
        DVD,
        BluRay,
        Fita
    };

private:
    std::string titulo;
    std::string codigo;
    int unidadesDisponiveis;
    Tipo tipo;

public:
    // Construtor
    Filme(const std::string& titulo, std::string codigo, Tipo tipo, int unidadesDisponiveis);

    // Destrutor
    ~Filme();

    // Getters
    const std::string& getTitulo() const;
    std::string getCodigo() const;
    int getUnidadesDisponiveis() const;
    Tipo getTipo() const;

    // Metodos da classe
    void adicionarUnidades(int quantidade);
    void removerUnidades(int quantidade);
    virtual double calcularValorLocacao(int dias) const = 0;

    // Overload for outputting Tipo enum to ostream
    friend std::ostream& operator<<(std::ostream& os, const Filme::Tipo& tipo);
};

inline std::ostream& operator<<(std::ostream& os, const Filme::Tipo& tipo) {
    switch (tipo) {
        case Filme::Tipo::DVD:
            os << "DVD";
            break;
        case Filme::Tipo::BluRay:
            os << "BluRay";
            break;
        case Filme::Tipo::Fita:
            os << "Fita";
            break;
    }
    return os;
}

#endif // FILME_HPP