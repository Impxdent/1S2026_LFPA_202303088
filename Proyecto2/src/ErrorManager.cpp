#include "ErrorManager.h"

std::vector<CustomError> ErrorManager::errors;

void ErrorManager::addError(const std::string& lex, const std::string& type, 
                             const std::string& desc, int l, int c) {
    int nextId = static_cast<int>(errors.size() + 1);
    errors.push_back({nextId, lex, type, desc, l, c});
}

void ErrorManager::clear() {
    errors.clear();
}