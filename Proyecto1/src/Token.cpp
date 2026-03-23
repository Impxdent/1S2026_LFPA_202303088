#include "Token.h"

Token::Token(TokenType type, const std::string& lexeme, int line, int column)
    : type(type), lexeme(lexeme), line(line), column(column) {}

TokenType Token::getType() const { return type; }
std::string Token::getLexeme() const { return lexeme; }
int Token::getLine() const { return line; }
int Token::getColumn() const { return column; }

std::string Token::getTypeName() const {
    switch (type) {
        case TokenType::RES_HOSPITAL: return "Reservada HOSPITAL";
        case TokenType::RES_PACIENTES: return "Reservada PACIENTES";
        case TokenType::RES_MEDICOS: return "Reservada MEDICOS";
        case TokenType::RES_CITAS: return "Reservada CITAS";
        case TokenType::RES_DIAGNOSTICOS: return "Reservada DIAGNOSTICOS";
        case TokenType::CADENA: return "Cadena de texto";
        case TokenType::ENTERO: return "Número Entero";
        case TokenType::CODIGO_ID: return "Código con guión";
        case TokenType::LITERAL_FECHA: return "Literal de Fecha";
        case TokenType::LITERAL_HORA: return "Literal de Hora";
        case TokenType::TIPO_SANGRE: return "Tipo de Sangre";
        case TokenType::LLAVE_A: return "Llave que abre '{'";
        case TokenType::LLAVE_C: return "Llave que cierra '}'";
        default: return "Token MedLang";
    }
}