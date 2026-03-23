#include "ErrorManager.h"

ErrorManager::ErrorManager() : currentId(1) {}

void ErrorManager::addError(const std::string& lexeme, const std::string& errorType, 
                            const std::string& description, int line, int column, ErrorSeverity severity) {
    errors.push_back({currentId++, lexeme, errorType, description, line, column, severity});
}

const std::vector<LexicalError>& ErrorManager::getErrors() const {
    return errors;
}

void ErrorManager::clearErrors() {
    errors.clear();
    currentId = 1;
}

bool ErrorManager::hasErrors() const {
    return !errors.empty();
}