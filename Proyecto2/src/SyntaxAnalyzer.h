#ifndef SYNTAXANALYZER_H
#define SYNTAXANALYZER_H

#include "LexicalAnalyzer.h"
#include "DataRemember.h" 
#include <memory>
#include <vector>
#include <string>

struct TreeNode {
    std::string label;
    bool isTerminal;
    std::vector<std::shared_ptr<TreeNode>> children;
    
    TreeNode(std::string l, bool t) : label(l), isTerminal(t) {}
};

class SyntaxAnalyzer {
private:
    LexicalAnalyzer& lexer;
    Token lookahead;

    BoardData board;
    ColumnData* currentCol = nullptr;
    TaskData* currentTask = nullptr;

    std::shared_ptr<TreeNode> parseTreeRoot = nullptr;

    void match(TokenType expected, std::shared_ptr<TreeNode> parent);
    
    void programa(std::shared_ptr<TreeNode> parent);
    void columnas(std::shared_ptr<TreeNode> parent);
    void columna(std::shared_ptr<TreeNode> parent);
    void tareas(std::shared_ptr<TreeNode> parent);
    void tarea(std::shared_ptr<TreeNode> parent);
    void atributos(std::shared_ptr<TreeNode> parent);
    void atributo(std::shared_ptr<TreeNode> parent);

public:
    SyntaxAnalyzer(LexicalAnalyzer& lex);
    void parse();
    
    BoardData getBoard() const { return board; }
    std::shared_ptr<TreeNode> getTreeRoot() const { return parseTreeRoot; } 
};

#endif