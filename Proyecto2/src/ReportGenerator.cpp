#include "ReportGenerator.h"
#include "ErrorManager.h"
#include <QFile>
#include <QTextStream>
#include <QMap>

//REPORTE KANBAN
void ReportGenerator::generateKanbanReport(const BoardData& board, const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);

    out << "<!DOCTYPE html><html><head><meta charset='utf-8'><title>Tablero Kanban</title>";
    out << "<style>";
    out << "body { font-family: Arial, sans-serif; background-color: #f4f5f7; padding: 20px; }";
    out << ".board-title { text-align: center; color: #172b4d; }";
    out << ".board { display: flex; gap: 20px; overflow-x: auto; padding-bottom: 20px; }";
    out << ".column { background-color: #ebecf0; border-radius: 8px; min-width: 300px; padding: 10px; box-shadow: 0 2px 4px rgba(0,0,0,0.1); }";
    out << ".col-title { font-size: 16px; font-weight: bold; margin-bottom: 10px; color: #172b4d; }";
    out << ".card { background: white; border-radius: 5px; padding: 12px; margin-bottom: 10px; box-shadow: 0 1px 2px rgba(0,0,0,0.2); border-left: 6px solid gray; }";
    out << ".card.ALTA { border-left-color: #ff5630; }";
    out << ".card.MEDIA { border-left-color: #ffab00; }";
    out << ".card.BAJA { border-left-color: #36b37e; }";
    out << ".task-title { font-weight: bold; margin-bottom: 8px; }";
    out << ".task-detail { font-size: 12px; color: #5e6c84; margin: 4px 0; }";
    out << "</style></head><body>";

    out << "<h1 class='board-title'>" << QString::fromStdString(board.name) << "</h1>";
    out << "<div class='board'>";

    for (const auto& col : board.columns) {
        out << "<div class='column'>";
        out << "<div class='col-title'>" << QString::fromStdString(col.name) << "</div>";
        for (const auto& t : col.tasks) {
            QString prio = QString::fromStdString(t.priority);
            out << "<div class='card " << prio << "'>";
            out << "<div class='task-title'>" << QString::fromStdString(t.name) << "</div>";
            out << "<div class='task-detail'><b>Resp:</b> " << QString::fromStdString(t.responsible) << "</div>";
            out << "<div class='task-detail'><b>Vence:</b> " << QString::fromStdString(t.dueDate) << "</div>";
            out << "<div class='task-detail'><b>Prioridad:</b> " << prio << "</div>";
            out << "</div>";
        }
        out << "</div>";
    }

    out << "</div></body></html>";
}

//REPORTE DE TRABAJO
struct WorkerStats { int alta = 0, media = 0, baja = 0, total = 0; };

void ReportGenerator::generateWorkloadReport(const BoardData& board, const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);

    QMap<QString, WorkerStats> stats;
    int totalBoardTasks = 0;

    for (const auto& col : board.columns) {
        for (const auto& t : col.tasks) {
            QString resp = QString::fromStdString(t.responsible);
            resp.remove("\""); // Quitar comillas
            stats[resp].total++;
            totalBoardTasks++;
            
            if (t.priority == "ALTA") stats[resp].alta++;
            else if (t.priority == "MEDIA") stats[resp].media++;
            else stats[resp].baja++;
        }
    }

    out << "<!DOCTYPE html><html><head><meta charset='utf-8'><title>Carga de Trabajo</title>";
    out << "<style>";
    out << "table { width: 100%; border-collapse: collapse; font-family: Arial; }";
    out << "th, td { border: 1px solid #ddd; padding: 8px; text-align: center; }";
    out << "th { background-color: #f2f2f2; }";
    out << ".bar-container { width: 100%; background-color: #e0e0e0; border-radius: 4px; }";
    out << ".bar { height: 20px; background-color: #4CAF50; border-radius: 4px; text-align: right; color: white; padding-right: 5px; line-height: 20px; font-size: 12px; }";
    out << "</style></head><body>";
    
    out << "<h2>Reporte de Carga por Responsable</h2>";
    out << "<table><tr><th>Responsable</th><th>Total Tareas</th><th>ALTA</th><th>MEDIA</th><th>BAJA</th><th>Distribución Visual</th></tr>";

    for (auto it = stats.begin(); it != stats.end(); ++it) {
        float percentage = totalBoardTasks > 0 ? (it.value().total * 100.0f / totalBoardTasks) : 0;
        out << "<tr>";
        out << "<td>" << it.key() << "</td>";
        out << "<td>" << it.value().total << "</td>";
        out << "<td>" << it.value().alta << "</td>";
        out << "<td>" << it.value().media << "</td>";
        out << "<td>" << it.value().baja << "</td>";
        out << "<td><div class='bar-container'><div class='bar' style='width: " << percentage << "%;'>" << QString::number(percentage, 'f', 1) << "%</div></div></td>";
        out << "</tr>";
    }

    out << "</table></body></html>";
}

//REPORTE DE ERRORES
void ReportGenerator::generateErrorReport(const QString& path) {
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&file);

    out << "<!DOCTYPE html><html><head><meta charset='utf-8'><title>Reporte de Errores</title>";
    out << "<style>";
    out << "table { width: 100%; border-collapse: collapse; font-family: Arial; }";
    out << "th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }";
    out << "th { background-color: #ffcccc; color: #cc0000; }";
    out << ".critico { color: #cc0000; font-weight: bold; }";
    out << ".error { color: #ff8800; font-weight: bold; }";
    out << ".advertencia { color: #aaaa00; font-weight: bold; }";
    out << "</style></head><body>";
    
    out << "<h2>Tabla de Errores Léxicos y Sintácticos</h2>";
    out << "<table><tr><th>No.</th><th>Lexema</th><th>Tipo</th><th>Descripción</th><th>Línea</th><th>Columna</th><th>Gravedad</th></tr>";

    int no = 1;
    for (const auto& err : ErrorManager::errors) {
        QString gravedad = "ERROR";
        QString cssClass = "error";
        if (err.type == "Léxico") { gravedad = "CRÍTICO"; cssClass = "critico"; }
        else if (err.type == "Semántico") { gravedad = "ADVERTENCIA"; cssClass = "advertencia"; }

        out << "<tr>";
        out << "<td>" << no++ << "</td>";
        out << "<td>" << QString::fromStdString(err.lexeme) << "</td>";
        out << "<td>" << QString::fromStdString(err.type) << "</td>";
        out << "<td>" << QString::fromStdString(err.description) << "</td>";
        out << "<td>" << err.line << "</td>";
        out << "<td>" << err.column << "</td>";
        out << "<td class='" << cssClass << "'>" << gravedad << "</td>";
        out << "</tr>";
    }

    out << "</table></body></html>";
}