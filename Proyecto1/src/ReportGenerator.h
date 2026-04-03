#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <QString>
#include <QTableWidget>

class ReportGenerator {
public:
    static bool generarReporteHTML(QTableWidget *tablaTokens, QTableWidget *tablaErrores, const QString &rutaArchivo);
};

#endif 