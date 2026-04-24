#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType {
    // Palabras Reservadas
    TABLERO, COLUMNA, TAREA, PRIORIDAD, RESPONSABLE, FECHA_LIMITE,
    // Prioridades
    ALTA, MEDIA, BAJA,
    // Literales y otros
    CADENA, FECHA, ENTERO,
    // Símbolos
    LLAVE_IZQ, LLAVE_DER, CORCHETE_IZQ, CORCHETE_DER, 
    DOS_PUNTOS, COMA, PUNTO_COMA,
    // Especiales
    ERROR, FIN_ARCHIVO
};

struct Token {
    TokenType type;
    std::string lexeme;
    int line;
    int column;

    // Utilidad para depuración y reportes
    std::string getTypeName() const; 
};

#endif