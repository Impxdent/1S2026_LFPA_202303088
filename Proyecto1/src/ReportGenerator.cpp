#include "ReportGenerator.h"
#include <QFile>
#include <QTextStream>

bool ReportGenerator::generarReporteHTML(QTableWidget *tablaTokens, QTableWidget *tablaErrores, const QString &rutaArchivo) {
    QFile archivo(rutaArchivo);
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false; 
    }

    QTextStream salida(&archivo);
    
    salida << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset='UTF-8'>\n";
    salida << "<title>Reporte de Análisis Léxico</title>\n";
    salida << "<style>\n";
    salida << "body { font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; margin: 40px; background-color: #f4f7f6; }\n";
    salida << "h1 { color: #2c3e50; text-align: center; }\n";
    salida << "h2 { color: #34495e; border-bottom: 2px solid #34495e; padding-bottom: 5px; }\n";
    salida << "table { width: 100%; border-collapse: collapse; margin-bottom: 30px; background-color: white; box-shadow: 0 1px 3px rgba(0,0,0,0.2); }\n";
    salida << "th, td { border: 1px solid #dddddd; padding: 12px; text-align: left; }\n";
    salida << "th { background-color: #2980b9; color: white; font-weight: bold; }\n";
    salida << ".error-th { background-color: #e74c3c; }\n";
    salida << "tr:nth-child(even) { background-color: #f9f9f9; }\n";
    salida << "</style>\n</head>\n<body>\n";
    
    salida << "<h1>Reporte de la aplicación MedLexer</h1>\n";
    
    salida << "<h2>Tokens Válidos Reconocidos</h2>\n";
    salida << "<table>\n<tr><th>Token</th><th>Lexema</th><th>Fila</th><th>Columna</th></tr>\n";
    for (int i = 0; i < tablaTokens->rowCount(); ++i) {
        salida << "<tr>";
        salida << "<td>" << tablaTokens->item(i, 0)->text() << "</td>";
        salida << "<td>" << tablaTokens->item(i, 1)->text().toHtmlEscaped() << "</td>";
        salida << "<td>" << tablaTokens->item(i, 2)->text() << "</td>";
        salida << "<td>" << tablaTokens->item(i, 3)->text() << "</td>";
        salida << "</tr>\n";
    }
    salida << "</table>\n";
    
    salida << "<h2>Errores Léxicos Encontrados</h2>\n";
    salida << "<table>\n<tr><th class='error-th'>Carácter Desconocido</th><th class='error-th'>Fila</th><th class='error-th'>Columna</th><th class='error-th'>Descripción</th></tr>\n";
    for (int i = 0; i < tablaErrores->rowCount(); ++i) {
        salida << "<tr>";
        salida << "<td>" << tablaErrores->item(i, 0)->text().toHtmlEscaped() << "</td>";
        salida << "<td>" << tablaErrores->item(i, 1)->text() << "</td>";
        salida << "<td>" << tablaErrores->item(i, 2)->text() << "</td>";
        salida << "<td>" << tablaErrores->item(i, 3)->text() << "</td>";
        salida << "</tr>\n";
    }
    salida << "</table>\n";
    
    salida << "</body>\n</html>";
    
    archivo.close();
    return true;
}