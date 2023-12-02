#ifndef FILME_HPP
#define FILME_HPP

#include <iostream>
#include <string>

/**
 * @file filme.hpp
 * @brief Declaração da classe Filme, seus métodos e atributos.
 * @details Este arquivo define a classe base Filme, que representa um filme genérico.
 *          As classes específicas (DVD, BluRay, Fita) herdam desta classe base.
 * @class Filme
 * @details A classe Filme contém atributos como título, código, quantidade de unidades disponíveis,
 *          tipo do filme (DVD, BluRay, Fita) e métodos para manipulação desses atributos.
 * @param titulo Título do filme.
 * @param codigo Código único do filme.
 * @param unidadesDisponiveis Número de unidades disponíveis para locação.
 * @param tipo Tipo do filme (DVD, BluRay, Fita).
 */

class Filme {
public:
    /**
     * @brief Enumeração que representa os tipos de filme.
     */
    enum class Tipo {
        DVD,    /**< Tipo de filme: DVD. */
        BluRay, /**< Tipo de filme: BluRay. */
        Fita    /**< Tipo de filme: Fita. */
    };

private:
    std::string titulo;            /**< Título do filme. */
    std::string codigo;            /**< Código único do filme. */
    Tipo tipo;                     /**< Tipo do filme (DVD, BluRay, Fita). */
    int unidadesDisponiveis;       /**< Número de unidades disponíveis para locação. */

public:
    /**
     * @brief Construtor da classe Filme.
     * @param titulo Título do filme.
     * @param codigo Código único do filme.
     * @param tipo Tipo do filme (DVD, BluRay, Fita).
     * @param unidadesDisponiveis Número de unidades disponíveis para locação.
     */
    Filme(const std::string& titulo, std::string codigo, Tipo tipo, int unidadesDisponiveis);

    /**
     * @brief Destrutor da classe Filme (virtual para permitir polimorfismo).
     */
    virtual ~Filme();

    /**
     * @brief Getter para o código do filme.
     * @return O código único do filme.
     */
    std::string getCodigo() const;

    /**
     * @brief Getter para o título do filme.
     * @return O título do filme.
     */
    const std::string& getTitulo() const;

    /**
     * @brief Getter para o número de unidades disponíveis.
     * @return O número de unidades disponíveis para locação.
     */
    int getUnidadesDisponiveis() const;

    /**
     * @brief Getter para o tipo do filme.
     * @return O tipo do filme (DVD, BluRay, Fita).
     */
    Tipo getTipo() const;

    /**
     * @brief Adiciona unidades disponíveis para locação.
     * @param quantidade A quantidade de unidades a serem adicionadas.
     */
    void adicionarUnidadesDisponiveis(int quantidade);

    /**
     * @brief Remove uma unidade disponível.
     */
    void removerUnidadeDisponivel();

    /**
     * @brief Calcula o valor total da locação do filme.
     * @param dias Número de dias pelos quais o filme será alugado.
     * @return O valor total da locação.
     * @note Este método é virtual puro para permitir polimorfismo nas classes derivadas.
     */
    virtual double calcularValorLocacao(int dias) const = 0;

    /**
     * @brief Sobrecarga do operador de saída para imprimir o tipo do filme.
     * @param os Objeto de fluxo de saída.
     * @param tipo Tipo do filme (DVD, BluRay, Fita).
     * @return O objeto de fluxo de saída.
     */
    friend std::ostream& operator<<(std::ostream& os, const Filme::Tipo& tipo);
};

/**
 * @brief Sobrecarga do operador de saída para imprimir o tipo do filme.
 * @param os Objeto de fluxo de saída.
 * @param tipo Tipo do filme (DVD, BluRay, Fita).
 * @return O objeto de fluxo de saída.
 */
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