/**
 * @file formatacao.cpp
 * @brief Implementação das funções de formatação de strings.
 */

#include "formatacao.hpp"
#include <algorithm>
#include <cctype>

/**
 * @brief Converte uma string para minúsculas.
 * 
 * @param input A string a ser convertida.
 * @return A string convertida para minúsculas.
 */
std::string toLowerCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){ return std::tolower(c); });
    return result;
}

/**
 * @brief Converte uma string para maiúsculas.
 * 
 * @param input A string a ser convertida.
 * @return A string convertida para maiúsculas.
 */
std::string toUpperCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){ return std::toupper(c); });
    return result;
}

/**
 * @brief Converte a primeira letra de cada palavra para maiúscula.
 * 
 * @param input A string a ser convertida.
 * @return A string com a primeira letra de cada palavra em maiúscula.
 */
std::string firstUpper(const std::string& input) {
    std::string result = input;
    bool capitalizeNext = true;
    for (char& c : result) {
        if (std::isalpha(c)) {
            if (capitalizeNext) {
                c = std::toupper(c);
                capitalizeNext = false;
            } else {
                c = std::tolower(c);
            }
        } else {
            capitalizeNext = true;
        }
    }
    return result;
}
