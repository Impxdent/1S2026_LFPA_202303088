#include "SyntaxAnalyzer.h"
#include "ErrorManager.h"
#include <QString>
#include <QStringList>

SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer& lex) : lexer(lex) {
    lookahead = lexer.nextToken();
}

void SyntaxAnalyzer::match(TokenType expected, std::shared_ptr<TreeNode> parent) {
    if (lookahead.type == expected) {
        if (parent) {
            parent->children.push_back(std::make_shared<TreeNode>(lookahead.lexeme, true));
        }
        lookahead = lexer.nextToken();
    } else {
        ErrorManager::addError(lookahead.lexeme, "Sintáctico", "Se esperaba un token de tipo diferente", lookahead.line, lookahead.column);
        if (lookahead.type != TokenType::FIN_ARCHIVO) {
            lookahead = lexer.nextToken();
        }
    }
}

void SyntaxAnalyzer::parse() {
    programa(nullptr);
}

void SyntaxAnalyzer::programa(std::shared_ptr<TreeNode> parent) {
    std::shared_ptr<TreeNode> node = std::make_shared<TreeNode>("<programa>", false);
    parseTreeRoot = node; 

    match(TokenType::TABLERO, node);
    board.name = lookahead.lexeme; 
    match(TokenType::CADENA, node);
    match(TokenType::LLAVE_IZQ, node);
    
    columnas(node);
    
    match(TokenType::LLAVE_DER, node);
    if(lookahead.type == TokenType::PUNTO_COMA) match(TokenType::PUNTO_COMA, node);
}

void SyntaxAnalyzer::columnas(std::shared_ptr<TreeNode> parent) {
    std::shared_ptr<TreeNode> node = std::make_shared<TreeNode>("<columnas>", false);
    parent->children.push_back(node);
    
    columna(node);
    if (lookahead.type == TokenType::COLUMNA) {
        columnas(node);
    }
}

void SyntaxAnalyzer::columna(std::shared_ptr<TreeNode> parent) {
    std::shared_ptr<TreeNode> node = std::make_shared<TreeNode>("<columna>", false);
    parent->children.push_back(node);

    match(TokenType::COLUMNA, node);
    
    ColumnData col;
    col.name = lookahead.lexeme; 
    board.columns.push_back(col);
    currentCol = &board.columns.back(); 
    
    match(TokenType::CADENA, node);
    match(TokenType::LLAVE_IZQ, node);
    
    if (lookahead.type == TokenType::TAREA) {
        tareas(node);
    }
    
    match(TokenType::LLAVE_DER, node);
    if(lookahead.type == TokenType::PUNTO_COMA) match(TokenType::PUNTO_COMA, node);
}

void SyntaxAnalyzer::tareas(std::shared_ptr<TreeNode> parent) {
    std::shared_ptr<TreeNode> node = std::make_shared<TreeNode>("<tareas>", false);
    parent->children.push_back(node);

    tarea(node);
    if (lookahead.type == TokenType::COMA) {
        match(TokenType::COMA, node);
        if (lookahead.type != TokenType::LLAVE_DER) {
            tareas(node);
        }
    }
}

void SyntaxAnalyzer::tarea(std::shared_ptr<TreeNode> parent) {
    std::shared_ptr<TreeNode> node = std::make_shared<TreeNode>("<tarea>", false);
    parent->children.push_back(node);

    match(TokenType::TAREA, node);
    match(TokenType::DOS_PUNTOS, node);
    
    TaskData t;
    t.name = lookahead.lexeme; 
    currentCol->tasks.push_back(t);
    currentTask = &currentCol->tasks.back(); 
    
    match(TokenType::CADENA, node);
    match(TokenType::CORCHETE_IZQ, node);
    atributos(node);
    match(TokenType::CORCHETE_DER, node);
}

void SyntaxAnalyzer::atributos(std::shared_ptr<TreeNode> parent) {
    std::shared_ptr<TreeNode> node = std::make_shared<TreeNode>("<atributos>", false);
    parent->children.push_back(node);

    atributo(node);
    if (lookahead.type == TokenType::COMA) {
        match(TokenType::COMA, node);
        if (lookahead.type != TokenType::CORCHETE_DER) {
            atributos(node);
        }
    }
}

void SyntaxAnalyzer::atributo(std::shared_ptr<TreeNode> parent) {
    std::shared_ptr<TreeNode> node = std::make_shared<TreeNode>("<atributo>", false);
    parent->children.push_back(node);

    if (lookahead.type == TokenType::PRIORIDAD) {
        match(TokenType::PRIORIDAD, node);
        match(TokenType::DOS_PUNTOS, node);
        
        if (lookahead.type == TokenType::ALTA || lookahead.type == TokenType::MEDIA || lookahead.type == TokenType::BAJA) {
            currentTask->priority = lookahead.lexeme; 
            node->children.push_back(std::make_shared<TreeNode>(lookahead.lexeme, true));
            lookahead = lexer.nextToken();
        } else {
            ErrorManager::addError(lookahead.lexeme, "Sintáctico", "Prioridad no válida", lookahead.line, lookahead.column);
        }
    } else if (lookahead.type == TokenType::RESPONSABLE) {
        match(TokenType::RESPONSABLE, node);
        match(TokenType::DOS_PUNTOS, node);
        
        currentTask->responsible = lookahead.lexeme; 
        match(TokenType::CADENA, node);
        
    } else if (lookahead.type == TokenType::FECHA_LIMITE) {
        match(TokenType::FECHA_LIMITE, node);
        match(TokenType::DOS_PUNTOS, node);
        
        currentTask->dueDate = lookahead.lexeme; 
        match(TokenType::FECHA, node);
    }
}