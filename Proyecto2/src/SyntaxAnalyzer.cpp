#include "SyntaxAnalyzer.h"
#include "ErrorManager.h"
#include <iostream>
#include <QString>      
#include <QStringList>  

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer& lex) : lexer(lex) {
    lookahead = lexer.nextToken();
}

void SyntaxAnalyzer::match(TokenType expected) {
    if (lookahead.type == expected) {
        lookahead = lexer.nextToken();
    } else {
        ErrorManager::addError(lookahead.lexeme, "Sintáctico", "Se esperaba un token de tipo diferente", lookahead.line, lookahead.column);

        if (lookahead.type != TokenType::FIN_ARCHIVO) {
            lookahead = lexer.nextToken();
        }
    }
}

void SyntaxAnalyzer::parse() {
    programa();
}

void SyntaxAnalyzer::programa() {
    match(TokenType::TABLERO);
    match(TokenType::CADENA);
    match(TokenType::LLAVE_IZQ);
    columnas();
    match(TokenType::LLAVE_DER);
    match(TokenType::PUNTO_COMA);
}

void SyntaxAnalyzer::columnas() {
    columna();
    if (lookahead.type == TokenType::COLUMNA) {
        columnas();
    }
}

void SyntaxAnalyzer::columna() {
    match(TokenType::COLUMNA);
    match(TokenType::CADENA);
    match(TokenType::LLAVE_IZQ);
    
    if (lookahead.type == TokenType::TAREA) {
        tareas();
    }
    
    match(TokenType::LLAVE_DER);
    match(TokenType::PUNTO_COMA);
}

void SyntaxAnalyzer::tareas() {
    tarea();
    if (lookahead.type == TokenType::COMA) {
        match(TokenType::COMA);
        
        if (lookahead.type != TokenType::LLAVE_DER) {
            tareas();
        }
    }
}

void SyntaxAnalyzer::tarea() {
    match(TokenType::TAREA);
    match(TokenType::DOS_PUNTOS);
    match(TokenType::CADENA);
    match(TokenType::CORCHETE_IZQ);
    atributos();
    match(TokenType::CORCHETE_DER);
}

void SyntaxAnalyzer::atributos() {
    atributo();
    if (lookahead.type == TokenType::COMA) {
        match(TokenType::COMA);
        
        if (lookahead.type != TokenType::CORCHETE_DER) {
            atributos();
        }
    }
}

void SyntaxAnalyzer::atributo() {
    if (lookahead.type == TokenType::PRIORIDAD) {
        match(TokenType::PRIORIDAD);
        match(TokenType::DOS_PUNTOS);
        if (lookahead.type == TokenType::ALTA || lookahead.type == TokenType::MEDIA || lookahead.type == TokenType::BAJA) {
            lookahead = lexer.nextToken();
        } else {
            ErrorManager::addError(lookahead.lexeme, "Sintáctico", "Prioridad no válida", lookahead.line, lookahead.column);
        }
    } else if (lookahead.type == TokenType::RESPONSABLE) {
        match(TokenType::RESPONSABLE);
        match(TokenType::DOS_PUNTOS);
        match(TokenType::CADENA);
    } else if (lookahead.type == TokenType::FECHA_LIMITE) {
        match(TokenType::FECHA_LIMITE);
        match(TokenType::DOS_PUNTOS);
        
        if (lookahead.type == TokenType::FECHA) {
            QString str = QString::fromStdString(lookahead.lexeme);
            QStringList partes = str.split("-");
            
            if (partes.size() == 3) {
                int mes = partes[1].toInt();
                int dia = partes[2].toInt();

                if (mes < 1 || mes > 12) {
                    ErrorManager::addError(lookahead.lexeme, "Semántico", "Mes fuera de rango (1-12)", lookahead.line, lookahead.column);
                }
                if (dia < 1 || dia > 31) {
                    ErrorManager::addError(lookahead.lexeme, "Semántico", "Día fuera de rango (1-31)", lookahead.line, lookahead.column);
                }
            }
        }

        match(TokenType::FECHA);
    }
}