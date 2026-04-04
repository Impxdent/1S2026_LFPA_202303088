#include "ReportGenerator.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <algorithm> 
#include <QMap>

bool ReportGenerator::generarReportesSemanticos(const Hospital &hospital, const QString &directorio) {
    
    QString css = "<style>"
                  "body { font-family: Arial, sans-serif; margin: 40px; background-color: #f9f9f9; }"
                  "h1 { color: #2c3e50; }"
                  "table { width: 100%; border-collapse: collapse; background-color: white; box-shadow: 0 1px 3px rgba(0,0,0,0.2); }"
                  "th, td { border: 1px solid #ddd; padding: 12px; text-align: left; }"
                  "th { background-color: #34495e; color: white; }"
                  ".estado { font-weight: bold; padding: 5px; border-radius: 4px; color: white; text-align: center; }"
                  ".verde { background-color: #27ae60; }"
                  ".naranja { background-color: #f39c12; }"
                  ".rojo { background-color: #c0392b; }"
                  ".azul { background-color: #2980b9; }"
                  "</style>";

    //reporte 1
    QFile archivo1(directorio + "/Reporte1_Historial_Pacientes.html");
    if (archivo1.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&archivo1);
        out << "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Reporte 1 - Pacientes</title>" << css << "</head><body>";
        out << "<h1>Reporte 1: Historial de Pacientes</h1><table>";
        out << "<tr><th>Paciente</th><th>Edad</th><th>Tipo Sangre</th><th>Condición / Medicamento</th><th>Estado</th></tr>";
        
        for (const Paciente &p : hospital.pacientes) {
            QString estadoClass = "verde";
            QString estadoTexto = "ACTIVO";
            QString infoMedica = "<i>Sin diagnóstico registrado</i>";

            if (!p.tiene_diagnostico) {
                estadoClass = "naranja";
                estadoTexto = "SIN DIAG.";
            } else {
                infoMedica = p.diagnostico.condicion + "<br><small>" + p.diagnostico.medicamento + " (" + p.diagnostico.dosis + ")</small>";
            }

            out << "<tr><td>" << p.nombre << "</td><td>" << p.edad << "</td><td>" << p.tipo_sangre << "</td>";
            out << "<td>" << infoMedica << "</td><td><div class='estado " << estadoClass << "'>" << estadoTexto << "</div></td></tr>";
        }
        out << "</table></body></html>";
        archivo1.close();
    } else { return false; }

    //reporte 2
    QFile archivo2(directorio + "/Reporte2_Carga_Medicos.html");
    if (archivo2.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&archivo2);
        out << "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Reporte 2 - Médicos</title>" << css << "</head><body>";
        out << "<h1>Reporte 2: Carga de Médicos por Especialidad</h1><table>";
        out << "<tr><th>Código</th><th>Médico</th><th>Especialidad</th><th>Total Citas</th><th>Carga de Trabajo</th></tr>";
        
        for (const Medico &m : hospital.medicos) {
            int citasTotales = 0;
            for (const Cita &c : hospital.citas) {
                if (c.medico == m.nombre) citasTotales++;
            }

            QString cargaClass = "verde";
            QString cargaTexto = "NORMAL";
            if (citasTotales <= 3) { cargaClass = "azul"; cargaTexto = "BAJA"; }
            else if (citasTotales >= 7 && citasTotales <= 8) { cargaClass = "naranja"; cargaTexto = "ALTA"; }
            else if (citasTotales >= 9) { cargaClass = "rojo"; cargaTexto = "SATURADA"; }

            out << "<tr><td>" << m.codigo << "</td><td>" << m.nombre << "</td><td>" << m.especialidad << "</td>";
            out << "<td>" << citasTotales << "</td><td><div class='estado " << cargaClass << "'>" << cargaTexto << "</div></td></tr>";
        }
        out << "</table></body></html>";
        archivo2.close();
    }

    //reporte 3
    QList<Cita> citasOrdenadas = hospital.citas;
    
    for (int i = 0; i < citasOrdenadas.size(); i++) {
        for (int j = i + 1; j < citasOrdenadas.size(); j++) {
            if (citasOrdenadas[i].medico == citasOrdenadas[j].medico && 
                citasOrdenadas[i].fecha == citasOrdenadas[j].fecha && 
                citasOrdenadas[i].hora == citasOrdenadas[j].hora) {
                citasOrdenadas[i].tiene_conflicto = true;
                citasOrdenadas[j].tiene_conflicto = true;
            }
        }
    }

    QFile archivo3(directorio + "/Reporte3_Agenda.html");
    if (archivo3.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&archivo3);
        out << "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Reporte 3 - Agenda</title>" << css << "</head><body>";
        out << "<h1>Reporte 3: Agenda de Citas</h1><table>";
        out << "<tr><th>Fecha y Hora</th><th>Paciente</th><th>Médico asignado</th><th>Estado</th></tr>";
        
        for (const Cita &c : citasOrdenadas) {
            QString estiloFila = c.tiene_conflicto ? "style='background-color: #fadbd8;'" : "";
            QString estadoClass = c.tiene_conflicto ? "rojo" : "verde";
            QString estadoTexto = c.tiene_conflicto ? "⚠ CONFLICTO" : "CONFIRMADA";

            out << "<tr " << estiloFila << "><td>" << c.fecha << " a las " << c.hora << "</td>";
            out << "<td>" << c.paciente << "</td><td>" << c.medico << "</td>";
            out << "<td><div class='estado " << estadoClass << "'>" << estadoTexto << "</div></td></tr>";
        }
        out << "</table></body></html>";
        archivo3.close();
    }

    //reporte4
    QFile archivo4(directorio + "/Reporte4_Estadistico.html");
    if (archivo4.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&archivo4);
        
        int totalPacientes = hospital.pacientes.size();
        int diagActivos = 0;
        int sumaEdades = 0;
        for (const Paciente& p : hospital.pacientes) {
            if (p.tiene_diagnostico) diagActivos++;
            sumaEdades += p.edad;
        }
        double porcDiag = totalPacientes > 0 ? (double)diagActivos / totalPacientes * 100 : 0;
        int promEdad = totalPacientes > 0 ? sumaEdades / totalPacientes : 0;

        out << "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Reporte 4 - Estadísticas</title>" << css << "</head><body>";
        out << "<h1>Reporte 4: Estadístico General del Hospital</h1>";
        
        out << "<h2>Sección A - Indicadores Clave</h2><ul>";
        out << "<li><b>Total Registros:</b> " << totalPacientes << " Pacientes, " << hospital.medicos.size() << " Médicos, " << hospital.citas.size() << " Citas.</li>";
        out << "<li><b>Pacientes con Diagnóstico Activo:</b> " << QString::number(porcDiag, 'f', 1) << "%</li>";
        out << "<li><b>Promedio de Edad:</b> " << promEdad << " años</li>";
        out << "</ul>";

        out << "<h2>Sección B - Distribución de Especialidades</h2><table>";
        out << "<tr><th>Especialidad</th><th>Barra de Ocupación</th></tr>";
        out << "<tr><td>General</td><td>agregar después...</td></tr>";
        out << "</table></body></html>";
        
        archivo4.close();
    }

    return true; 
}

//reporte 0 (tokens)
    bool ReportGenerator::generarReporteHTML(QTableWidget *tablaTokens, QTableWidget *tablaErrores, const QString &rutaArchivo) {
        QFile archivo(rutaArchivo);
        if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
            return false; 
        }

        QTextStream salida(&archivo);
        
        salida << "<!DOCTYPE html>\n<html>\n<head>\n<meta charset='UTF-8'>\n";
        salida << "<title>Reporte Léxico</title>\n";
        salida << "<style>\n";
        salida << "body { font-family: Arial, sans-serif; margin: 40px; background-color: #f4f7f6; }\n";
        salida << "h1, h2 { color: #2c3e50; }\n";
        salida << "table { width: 100%; border-collapse: collapse; margin-bottom: 30px; background-color: white; }\n";
        salida << "th, td { border: 1px solid #dddddd; padding: 12px; text-align: left; }\n";
        salida << "th { background-color: #2980b9; color: white; }\n";
        salida << ".error-th { background-color: #e74c3c; }\n";
        salida << "</style>\n</head>\n<body>\n";
        
        salida << "<h1>Reporte de Análisis Léxico</h1>\n";
        
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
        salida << "</table>\n</body>\n</html>";
        
        archivo.close();
        return true; 
    }

//generar archivo .dot de graphviz
bool ReportGenerator::generarReporteGraphviz(const Hospital &hospital, const QString &directorio) {
    QFile archivo(directorio + "/hospital.dot");
    if (!archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return false;
    }

    QTextStream out(&archivo);
    
    out << "digraph Hospital {\n";
    out << "rankdir=TB; node [shape=box, style=filled, fontname=\"Arial\"];\n";
    out << "H  [label=\"Hospital\", fillcolor=\"#1A4731\", fontcolor=white, shape=ellipse];\n";
    out << "P  [label=\"PACIENTES\", fillcolor=\"#2E7D52\", fontcolor=white];\n";
    out << "M  [label=\"MEDICOS\", fillcolor=\"#2E7D52\", fontcolor=white];\n";
    out << "C  [label=\"CITAS\", fillcolor=\"#2E7D52\", fontcolor=white];\n";
    out << "D  [label=\"DIAGNOSTICOS\", fillcolor=\"#2E7D52\", fontcolor=white];\n";
    out << "H -> P; H -> M; H -> C; H -> D;\n\n";

    QMap<QString, QString> idPacientes;
    QMap<QString, QString> idMedicos;

    for (int i = 0; i < hospital.pacientes.size(); i++) {
        QString id = "p" + QString::number(i);
        const Paciente &pac = hospital.pacientes[i];
        idPacientes[pac.nombre] = id; // Guardamos el ID para usarlo luego en citas y diagnósticos

        out << id << " [label=\"" << pac.nombre << "\\n" << pac.tipo_sangre << " | Hab. " 
            << pac.habitacion << "\", fillcolor=\"#D4EDDA\"];\n";
        out << "P -> " << id << ";\n";
    }
    out << "\n";

    for (int i = 0; i < hospital.medicos.size(); i++) {
        QString id = "m" + QString::number(i);
        const Medico &med = hospital.medicos[i];
        idMedicos[med.nombre] = id;

        out << id << " [label=\"" << med.nombre << "\\n" << med.codigo << " | " 
            << med.especialidad << "\", fillcolor=\"#D6EAF8\"];\n";
        out << "M -> " << id << ";\n";
    }
    out << "\n";

    for (const Cita &cita : hospital.citas) {
        QString idP = idPacientes.value(cita.paciente, "");
        QString idM = idMedicos.value(cita.medico, "");
        
        if (!idP.isEmpty() && !idM.isEmpty()) {
            out << idP << " -> " << idM << " [label=\"" << cita.fecha << "  " 
                << cita.hora << "\", color=\"#E67E22\", style=dashed];\n";
        }
    }
    out << "\n";

    int diagCounter = 0;
    for (const Paciente &pac : hospital.pacientes) {
        if (pac.tiene_diagnostico) {
            QString idDiag = "d" + QString::number(diagCounter++);
            QString idP = idPacientes.value(pac.nombre, "");

            out << idDiag << " [label=\"" << pac.diagnostico.condicion << "\\n" 
                << pac.diagnostico.medicamento << " / " << pac.diagnostico.dosis 
                << "\", fillcolor=\"#FDEBD0\"];\n";
            out << "D -> " << idDiag << ";\n";
            out << idDiag << " -> " << idP << " [label=\"diagnóstico activo\", color=\"#C0392B\"];\n";
        }
    }

    out << "}\n";
    archivo.close();
    return true;
}