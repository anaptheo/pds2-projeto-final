#include "formatacao.hpp"
#include <iostream>
#include <string>
#include <algorithm>
#include <deque>
#include <cctype>
#include <iomanip>



std::string toLowerCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){ return std::tolower(c); });
    return result;
}

std::string toUpperCase(const std::string& input) {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c){ return std::toupper(c); });
    return result;
}

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


std::string retornaStringFormatada(std::deque<std::string> palavra) {
    std::string string_formatada;
    for (std::string c : palavra) { 
        string_formatada = string_formatada + " " + c; 
    }
    string_formatada = firstUpper(string_formatada); 
    return string_formatada;
}