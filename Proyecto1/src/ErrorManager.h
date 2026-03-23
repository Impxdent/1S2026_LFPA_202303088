#ifndef ERRORMANAGER_H
#define ERRORMANAGER_H

#include <string>
#include <vector>

// Gravedad del error según el documento
enum class ErrorSeverity {
    ERROR,
    CRITICO
};

// Estructura para almacenar cada error léxico
struct LexicalError {
    int id;
    std::string lexeme;
    std::string errorType;
    std::string description;
    int line;
    int column;
    ErrorSeverity severity;
};

class ErrorManager {
public:
    ErrorManager();
    
    void addError(const std::string& lexeme, const std::string& errorType, 
                  const std::string& description, int line, int column, ErrorSeverity severity);
    const std::vector<LexicalError>& getErrors() const;
    void clearErrors();
    bool hasErrors() const;

private:
    std::vector<LexicalError> errors;
    int currentId;
};

#endif 