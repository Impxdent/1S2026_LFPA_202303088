#include "Token.h"

std::string Token::getTypeName() const {
    switch (type) {
        case TokenType::TABLERO:      return "TABLERO";
        case TokenType::COLUMNA:      return "COLUMNA";
        case TokenType::TAREA:        return "tarea";
        case TokenType::PRIORIDAD:    return "prioridad";
        case TokenType::RESPONSABLE:  return "responsable";
        case TokenType::FECHA_LIMITE: return "fecha_limite";
        case TokenType::ALTA:         return "ALTA";
        case TokenType::MEDIA:        return "MEDIA";
        case TokenType::BAJA:         return "BAJA";
        case TokenType::CADENA:       return "CADENA";
        case TokenType::FECHA:        return "FECHA";
        case TokenType::ENTERO:       return "ENTERO";
        case TokenType::LLAVE_IZQ:    return "LLAVE_IZQ {";
        case TokenType::LLAVE_DER:    return "LLAVE_DER }";
        case TokenType::CORCHETE_IZQ: return "CORCHETE_IZQ [";
        case TokenType::CORCHETE_DER: return "CORCHETE_DER ]";
        case TokenType::DOS_PUNTOS:   return "DOS_PUNTOS :";
        case TokenType::COMA:         return "COMA ,";
        case TokenType::PUNTO_COMA:   return "PUNTO_COMA ;";
        case TokenType::ERROR:        return "ERROR";
        case TokenType::FIN_ARCHIVO:  return "FIN_ARCHIVO";
        default:                      return "DESCONOCIDO";
    }
}