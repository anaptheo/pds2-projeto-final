#ifndef FORMATACAO_H
#define FORMATACAO_H

#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <deque>


std::string toLowerCase(const std::string& input);

std::string toUpperCase(const std::string& input);

std::string firstUpper(const std::string& input);

std::string retornaStringFormatada(std::deque<std::string> palavra);


#endif