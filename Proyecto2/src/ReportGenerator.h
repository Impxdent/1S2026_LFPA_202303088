#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include "DataRemember.h"
#include <QString>

class ReportGenerator {
public:
    static void generateKanbanReport(const BoardData& board, const QString& path);
    static void generateWorkloadReport(const BoardData& board, const QString& path);
    static void generateErrorReport(const QString& path);
};

#endif