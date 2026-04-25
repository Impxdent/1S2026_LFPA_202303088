#include "Token.h"

std::string Token::getTypeName() const {
    switch (type) {
        // Palabras reservadas
        case TokenType::TABLERO:      return "Palabra reservada raíz";
        case TokenType::COLUMNA:      return "Palabra reservada de sección";
        case TokenType::TAREA:        return "Palabra reservada de elemento";
        
        // Atributos
        case TokenType::PRIORIDAD:    
        case TokenType::RESPONSABLE:  
        case TokenType::FECHA_LIMITE: return "Palabra reservada de atributo";
        
        // Enumeración
        case TokenType::ALTA:         
        case TokenType::MEDIA:        
        case TokenType::BAJA:         return "Enumeración";
        
        // Literales
        case TokenType::CADENA:       return "Literal de texto";
        case TokenType::FECHA:        return "Literal de fecha";
        case TokenType::ENTERO:       return "Literal numérico";
        
        // Símbolos
        case TokenType::LLAVE_IZQ:    
        case TokenType::LLAVE_DER:    
        case TokenType::CORCHETE_IZQ: 
        case TokenType::CORCHETE_DER: 
        case TokenType::DOS_PUNTOS:   
        case TokenType::COMA:         
        case TokenType::PUNTO_COMA:   return "Símbolos";
        
        // Otros
        case TokenType::ERROR:        return "Error Léxico";
        case TokenType::FIN_ARCHIVO:  return "Fin de Archivo";
        default:                      return "Desconocido";
    }
}