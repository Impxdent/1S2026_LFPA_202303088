#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include <string>
#include <vector>

struct CustomError {
    int id;
    std::string lexeme;
    std::string type;       // "Léxico" o "Sintáctico"
    std::string description;
    int line;
    int column;
};

class ErrorManager {
public:
    static std::vector<CustomError> errors;

    static void addError(const std::string& lex, const std::string& type, 
                         const std::string& desc, int l, int c);
    
    static void clear(); // Útil para reiniciar el análisis en la GUI
};

#endif