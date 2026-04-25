#ifndef DATAREMEMBER_H
#define DATAREMEMBER_H

#include <string>
#include <vector>

struct TaskData {
    std::string name;
    std::string priority = "BAJA"; // Valor por defecto
    std::string responsible = "Sin asignar";
    std::string dueDate = "Sin fecha";
};

struct ColumnData {
    std::string name;
    std::vector<TaskData> tasks;
};

struct BoardData {
    std::string name;
    std::vector<ColumnData> columns;
};

#endif