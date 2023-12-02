#ifndef FORMATACAO_H
#define FORMATACAO_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <iomanip>

/**
 * @file formatacao.hpp
 * @brief Funções para formatação de strings.
 */

/**
 * @brief Converte uma string para letras minúsculas.
 * 
 * @param input A string a ser convertida.
 * @return A string convertida para letras minúsculas.
 */
std::string toLowerCase(const std::string& input);

/**
 * @brief Converte uma string para letras maiúsculas.
 * 
 * @param input A string a ser convertida.
 * @return A string convertida para letras maiúsculas.
 */
std::string toUpperCase(const std::string& input);

/**
 * @brief Converte a primeira letra de uma string para maiúscula.
 * 
 * @param input A string a ser convertida.
 * @return A string com a primeira letra em maiúscula.
 */
std::string firstUpper(const std::string& input);

#endif // FORMATACAO_H
