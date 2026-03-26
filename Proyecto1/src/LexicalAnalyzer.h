#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <QString>
#include <QList>
#include "Token.h"

class LexicalAnalyzer {
public:
    LexicalAnalyzer();
    
    QList<Token> analizar(const QString& entrada);
};

#endif