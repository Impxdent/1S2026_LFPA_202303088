#ifndef DATAEXTRACTOR_H
#define DATAEXTRACTOR_H

#include "Token.h"
#include "Estructuras.h"
#include <QList>

class DataExtractor {
public:
    static Hospital extraerDatos(const QList<Token>& tokens);
};

#endif 