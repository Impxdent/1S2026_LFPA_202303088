#ifndef TOKEN_H
#define TOKEN_H

#include <string>

// Definición de todos los tipos de tokens según el alcance
enum class TokenType {
    // Palabras Reservadas
    RES_HOSPITAL, RES_PACIENTES, RES_MEDICOS, RES_CITAS, RES_DIAGNOSTICOS,
    RES_PACIENTE, RES_MEDICO, RES_CITA, RES_DIAGNOSTICO, RES_CON,
    
    // Atributos de elementos
    ATTR_EDAD, ATTR_TIPO_SANGRE, ATTR_HABITACION, ATTR_ESPECIALIDAD, 
    ATTR_CODIGO, ATTR_FECHA, ATTR_HORA, ATTR_CONDICION, ATTR_MEDICAMENTO, ATTR_DOSIS,
    
    // Enumeraciones
    ENUM_ESPECIALIDAD, ENUM_DOSIS,
    
    // Literales y Patrones Complejos
    TIPO_SANGRE, LITERAL_FECHA, LITERAL_HORA, ENTERO, CADENA, CODIGO_ID,
    
    // Símbolos Estructurales
    LLAVE_A,      // {
    LLAVE_C,      // }
    CORCHETE_A,   // [
    CORCHETE_C,   // ]
    DOS_PUNTOS,   // :
    COMA,         // ,
    
    // Control
    DESCONOCIDO, 
    FIN_ARCHIVO
};

class Token {
public:
    Token(TokenType type, const std::string& lexeme, int line, int column);

    TokenType getType() const;
    std::string getLexeme() const;
    int getLine() const;
    int getColumn() const;
    std::string getTypeName() const;

private:
    TokenType type;
    std::string lexeme;
    int line;
    int column;
};

#endif // TOKEN_H