#ifndef TOKEN_H
#define TOKEN_H

#include <QString>

//lista de todo lo que nuestro lenguaje entiende
enum TokenType {
    PalabraReservada, // HOSPITAL, paciente, medico, etc
    Identificador,    // CARDIOLOGIA, O+, etc
    Numero,           // 45
    Cadena,           // "O+"
    Fecha,            // 2026-03-25
    Hora,             // 14:30
    LlaveAbre,        // {
    LlaveCierra,      // }
    CorcheteAbre,     // [
    CorcheteCierra,   // ]
    DosPuntos,        // :
    Coma,             // ,
    ErrorLexico       // $, %, # o cadenas sin cerrar
};

// La estructura de cada pieza encontrada
struct Token {
    TokenType tipo;
    QString lexema;
    int fila;
    int columna;
};

#endif