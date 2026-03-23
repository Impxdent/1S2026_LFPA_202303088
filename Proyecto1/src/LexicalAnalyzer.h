#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <string>
#include <vector>
#include "Token.h"
#include "ErrorManager.h"

class LexicalAnalyzer {
public:
    LexicalAnalyzer(const std::string& sourceCode, ErrorManager& errorManager);
    Token nextToken();
    std::vector<Token> tokenize();

private:
    std::string source;
    int position;
    int line;
    int column;
    ErrorManager& errorManager;

    char peek() const;
    char peekNext() const;
    char getChar();
    bool isAtEnd() const;
    void skipWhitespace();
    
    TokenType resolveKeywordOrEnum(const std::string& lexeme) const;
    TokenType resolveStringContent(const std::string& content) const;
    bool isLetter(char c) const;
    bool isDigit(char c) const;
};

#endif 