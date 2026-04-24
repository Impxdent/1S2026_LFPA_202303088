#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include "Token.h"
#include "ErrorManager.h"
#include <vector>
#include <string>

class ReportGenerator {
public:
    static void generateTokenReport(const std::string& filename, const std::vector<Token>& tokens);
    
    static void generateErrorReport(const std::string& filename, const std::vector<CustomError>& errors);
    
    static void generateKanbanReport(const std::string& filename);

private:
    static std::string getCSS(); 
};

#endif