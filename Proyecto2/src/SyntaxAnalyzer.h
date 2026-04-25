#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H

#include "LexicalAnalyzer.h"
#include "DataRemember.h"
#include <memory>

class SyntaxAnalyzer {
private:
    LexicalAnalyzer& lexer;
    Token lookahead;

    BoardData board;
    ColumnData* currentCol = nullptr;
    TaskData* currentTask = nullptr;

    void match(TokenType expected);
    
    void programa();
    void columnas();
    void columna();
    void tareas();
    void tarea();
    void atributos();
    void atributo();

public:
    SyntaxAnalyzer(LexicalAnalyzer& lex);
    void parse();

    BoardData getBoard() const { return board; }
};

#endif