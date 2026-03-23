#include "LexicalAnalyzer.h"
#include <cctype>
#include <iostream>

LexicalAnalyzer::LexicalAnalyzer(const std::string& sourceCode, ErrorManager& errorManager)
    : source(sourceCode), position(0), line(1), column(1), errorManager(errorManager) {}

char LexicalAnalyzer::peek() const {
    if (isAtEnd()) return '\0';
    return source[position];
}

char LexicalAnalyzer::peekNext() const {
    if (position + 1 >= source.length()) return '\0';
    return source[position + 1];
}

char LexicalAnalyzer::getChar() {
    char c = source[position++];
    if (c == '\n') {
        line++;
        column = 1;
    } else {
        column++;
    }
    return c;
}

bool LexicalAnalyzer::isAtEnd() const {
    return position >= source.length();
}

void LexicalAnalyzer::skipWhitespace() {
    while (!isAtEnd() && (peek() == ' ' || peek() == '\t' || peek() == '\n' || peek() == '\r')) {
        getChar();
    }
}

bool LexicalAnalyzer::isLetter(char c) const {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool LexicalAnalyzer::isDigit(char c) const {
    return c >= '0' && c <= '9';
}

//analiza el tipo de palabra
TokenType LexicalAnalyzer::resolveKeywordOrEnum(const std::string& lexeme) const {
    if (lexeme == "HOSPITAL") return TokenType::RES_HOSPITAL;
    if (lexeme == "PACIENTES") return TokenType::RES_PACIENTES;
    if (lexeme == "MEDICOS") return TokenType::RES_MEDICOS;
    if (lexeme == "CITAS") return TokenType::RES_CITAS;
    if (lexeme == "DIAGNOSTICOS") return TokenType::RES_DIAGNOSTICOS;
    if (lexeme == "paciente") return TokenType::RES_PACIENTE;
    if (lexeme == "medico") return TokenType::RES_MEDICO;
    if (lexeme == "cita") return TokenType::RES_CITA;
    if (lexeme == "diagnostico") return TokenType::RES_DIAGNOSTICO;
    if (lexeme == "con") return TokenType::RES_CON;
    
    if (lexeme == "edad") return TokenType::ATTR_EDAD;
    if (lexeme == "tipo_sangre") return TokenType::ATTR_TIPO_SANGRE;
    if (lexeme == "habitacion") return TokenType::ATTR_HABITACION;
    if (lexeme == "especialidad") return TokenType::ATTR_ESPECIALIDAD;
    if (lexeme == "codigo") return TokenType::ATTR_CODIGO;
    if (lexeme == "fecha") return TokenType::ATTR_FECHA;
    if (lexeme == "hora") return TokenType::ATTR_HORA;
    if (lexeme == "condicion") return TokenType::ATTR_CONDICION;
    if (lexeme == "medicamento") return TokenType::ATTR_MEDICAMENTO;
    if (lexeme == "dosis") return TokenType::ATTR_DOSIS;

    if (lexeme == "CARDIOLOGIA" || lexeme == "NEUROLOGIA" || lexeme == "PEDIATRIA" ||
        lexeme == "CIRUGIA" || lexeme == "MEDICINA_GENERAL" || lexeme == "ONCOLOGIA") {
        return TokenType::ENUM_ESPECIALIDAD;
    }
    if (lexeme == "DIARIA" || lexeme == "CADA_8_HORAS" || 
        lexeme == "CADA_12_HORAS" || lexeme == "SEMANAL") {
        return TokenType::ENUM_DOSIS;
    }

    return TokenType::DESCONOCIDO;
}

TokenType LexicalAnalyzer::resolveStringContent(const std::string& content) const {
    if (content == "A+" || content == "A-" || content == "B+" || content == "B-" ||
        content == "O+" || content == "O-" || content == "AB+" || content == "AB-") {
        return TokenType::TIPO_SANGRE;
    }
    
    if (content.length() >= 5 && content[3] == '-') {
        bool isId = true;
        for (int i = 0; i < 3; i++) {
            if (!isLetter(content[i])) isId = false;
        }
        for (int i = 4; i < content.length(); i++) {
            if (!isDigit(content[i])) isId = false;
        }
        if (isId) return TokenType::CODIGO_ID;
    }

    return TokenType::CADENA;
}

Token LexicalAnalyzer::nextToken() {
    skipWhitespace();

    if (isAtEnd()) {
        return Token(TokenType::FIN_ARCHIVO, "EOF", line, column);
    }

    int startLine = line;
    int startColumn = column;
    char c = getChar();
    std::string lexeme = "";
    lexeme += c;

    if (c == '{') return Token(TokenType::LLAVE_A, lexeme, startLine, startColumn);
    if (c == '}') return Token(TokenType::LLAVE_C, lexeme, startLine, startColumn);
    if (c == '[') return Token(TokenType::CORCHETE_A, lexeme, startLine, startColumn);
    if (c == ']') return Token(TokenType::CORCHETE_C, lexeme, startLine, startColumn);
    if (c == ':') return Token(TokenType::DOS_PUNTOS, lexeme, startLine, startColumn);
    if (c == ',') return Token(TokenType::COMA, lexeme, startLine, startColumn);

    if (isLetter(c)) {
        while (isLetter(peek()) || isDigit(peek()) || peek() == '_') {
            lexeme += getChar();
        }
        TokenType type = resolveKeywordOrEnum(lexeme);
        if (type == TokenType::DESCONOCIDO) {
            errorManager.addError(lexeme, "Palabra desconocida", "La palabra no es reservada ni enum", startLine, startColumn, ErrorSeverity::ERROR);
        }
        return Token(type, lexeme, startLine, startColumn);
    }

    if (isDigit(c)) {
        bool isDate = false;
        bool isTime = false;

        while (isDigit(peek()) || peek() == '-' || peek() == ':') {
            char nextC = peek();
            if (nextC == '-') isDate = true;
            if (nextC == ':') isTime = true;
            lexeme += getChar();
        }

        if (isDate) {
            if (lexeme.length() != 10) {
                errorManager.addError(lexeme, "Formato de fecha inválido", "El formato esperado es AAAA-MM-DD", startLine, startColumn, ErrorSeverity::ERROR);
            }
            return Token(TokenType::LITERAL_FECHA, lexeme, startLine, startColumn);
        } else if (isTime) {
            if (lexeme.length() != 5) {
                errorManager.addError(lexeme, "Formato de hora inválido", "El formato esperado es HH:MM", startLine, startColumn, ErrorSeverity::ERROR);
            }
            return Token(TokenType::LITERAL_HORA, lexeme, startLine, startColumn);
        }

        return Token(TokenType::ENTERO, lexeme, startLine, startColumn);
    }

    if (c == '"') {
        lexeme = "";
        bool closed = false;
        
        while (!isAtEnd()) {
            if (peek() == '"') {
                getChar();
                closed = true;
                break;
            }
            if (peek() == '\n') {
                break;
            }
            lexeme += getChar();
        }

        if (!closed) {
            errorManager.addError(lexeme, "Cadena sin cerrar", "Falta comilla doble de cierre antes de salto de línea o fin de archivo", startLine, startColumn, ErrorSeverity::CRITICO);
            return Token(TokenType::DESCONOCIDO, lexeme, startLine, startColumn);
        }

        TokenType type = resolveStringContent(lexeme);
        return Token(type, lexeme, startLine, startColumn);
    }

    errorManager.addError(lexeme, "Carácter Ilegal", "El símbolo no pertenece al alfabeto del lenguaje", startLine, startColumn, ErrorSeverity::ERROR);
    return Token(TokenType::DESCONOCIDO, lexeme, startLine, startColumn);
}

std::vector<Token> LexicalAnalyzer::tokenize() {
    std::vector<Token> tokens;
    Token t = nextToken();
    while (t.getType() != TokenType::FIN_ARCHIVO) {
        if (t.getType() != TokenType::DESCONOCIDO) {
            tokens.push_back(t);
        }
        t = nextToken();
    }
    tokens.push_back(t);
    return tokens;
}