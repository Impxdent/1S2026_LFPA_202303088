#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include "Token.h"
#include "ErrorManager.h"
#include <vector>
#include <string>

class ReportGenerator {
public:
    // Reporte 1: Tabla de Tokens
    static void generateTokenReport(const std::string& filename, const std::vector<Token>& tokens);
    
    // Reporte 2: Tabla de Errores
    static void generateErrorReport(const std::string& filename, const std::vector<CustomError>& errors);
    
    // Reporte 3: Visualización del Tablero Kanban (Este se llenará con la lógica del Parser)
    static void generateKanbanReport(const std::string& filename);

private:
    static std::string getCSS(); // CSS común para los reportes
};

#endif