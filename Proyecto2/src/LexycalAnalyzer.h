#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include "Token.h"
#include <vector>
#include <string>

class LexicalAnalyzer {
private:
    std::string source;
    size_t cursor;
    int line;
    int column;

    char peek();
    char advance();
    void skipWhitespace();
    
    // Métodos para estados del AFD
    Token readString();
    Token readNumberOrDate();
    Token readIdentifier();

public:
    LexicalAnalyzer(const std::string& input);
    Token nextToken(); // El método principal solicitado
};

#endif