#include "LexicalAnalyzer.h"
#include "ErrorManager.h"
#include <cctype>

LexicalAnalyzer::LexicalAnalyzer(const std::string& input) 
    : source(input), cursor(0), line(1), column(1) {}

char LexicalAnalyzer::peek() {
    if (cursor >= source.length()) return '\0';
    return source[cursor];
}

char LexicalAnalyzer::advance() {
    char current = peek();
    cursor++;
    if (current == '\n') {
        line++;
        column = 1;
    } else {
        column++;
    }
    return current;
}

void LexicalAnalyzer::skipWhitespace() {
    while (isspace(peek())) {
        advance();
    }
}

Token LexicalAnalyzer::nextToken() {
    skipWhitespace();

    int startLine = line;
    int startCol = column;

    if (peek() == '\0') {
        return {TokenType::FIN_ARCHIVO, "$", startLine, startCol};
    }

    char c = peek();

    if (isalpha(c)) {
        return readIdentifier();
    }

    if (isdigit(c)) {
        return readNumberOrDate();
    }

    if (c == '"') {
        return readString();
    }

    char current = advance();
    switch (current) {
        case '{': return {TokenType::LLAVE_IZQ, "{", startLine, startCol};
        case '}': return {TokenType::LLAVE_DER, "}", startLine, startCol};
        case '[': return {TokenType::CORCHETE_IZQ, "[", startLine, startCol};
        case ']': return {TokenType::CORCHETE_DER, "]", startLine, startCol};
        case ':': return {TokenType::DOS_PUNTOS, ":", startLine, startCol};
        case ',': return {TokenType::COMA, ",", startLine, startCol};
        case ';': return {TokenType::PUNTO_COMA, ";", startLine, startCol};
        default:
            std::string s(1, current);
            ErrorManager::addError(s, "Léxico", "Carácter no reconocido por el lenguaje", startLine, startCol);
            return {TokenType::ERROR, s, startLine, startCol};
    }
}

Token LexicalAnalyzer::readIdentifier() {
    int startCol = column;
    std::string buffer;
    
    while (isalnum(peek()) || peek() == '_') {
        buffer += advance();
    }

    if (buffer == "TABLERO")     return {TokenType::TABLERO, buffer, line, startCol};
    if (buffer == "COLUMNA")     return {TokenType::COLUMNA, buffer, line, startCol};
    if (buffer == "tarea")       return {TokenType::TAREA, buffer, line, startCol};
    if (buffer == "prioridad")   return {TokenType::PRIORIDAD, buffer, line, startCol};
    if (buffer == "responsable") return {TokenType::RESPONSABLE, buffer, line, startCol};
    if (buffer == "fecha_limite") return {TokenType::FECHA_LIMITE, buffer, line, startCol};
    if (buffer == "ALTA")        return {TokenType::ALTA, buffer, line, startCol};
    if (buffer == "MEDIA")       return {TokenType::MEDIA, buffer, line, startCol};
    if (buffer == "BAJA")        return {TokenType::BAJA, buffer, line, startCol};
    return {TokenType::ERROR, buffer, line, startCol};
}

Token LexicalAnalyzer::readString() {
    int startCol = column;
    advance(); 
    std::string buffer;

    while (peek() != '"' && peek() != '\0') {
        buffer += advance();
    }

    if (peek() == '"') {
        advance(); 
        return {TokenType::CADENA, buffer, line, startCol};
    }

    ErrorManager::addError(buffer, "Léxico", "Cadena de texto sin cerrar", line, startCol);
    return {TokenType::ERROR, buffer, line, startCol};
}

Token LexicalAnalyzer::readNumberOrDate() {
    int startCol = column;
    std::string buffer;

    while (isdigit(peek()) || peek() == '-') {
        buffer += advance();
    }

    if (buffer.length() == 10 && buffer[4] == '-' && buffer[7] == '-') {
        return {TokenType::FECHA, buffer, line, startCol};
    }

    bool isOnlyDigits = true;
    for (char c : buffer) if (!isdigit(c)) isOnlyDigits = false;

    if (isOnlyDigits) {
        return {TokenType::ENTERO, buffer, line, startCol};
    }

    ErrorManager::addError(buffer, "Léxico", "Formato de fecha o número inválido", line, startCol);
    return {TokenType::ERROR, buffer, line, startCol};
}