#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <QString>
#include <QTableWidget>
#include "Estructuras.h"

class ReportGenerator {
public:
    static bool generarReporteHTML(QTableWidget *tablaTokens, QTableWidget *tablaErrores, const QString &rutaArchivo);
    static bool generarReportesSemanticos(const Hospital &hospital, const QString &directorio);
    static bool generarReporteGraphviz(const Hospital &hospital, const QString &directorio);
};

#endif