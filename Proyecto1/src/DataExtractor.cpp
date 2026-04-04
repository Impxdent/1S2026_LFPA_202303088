#include "DataExtractor.h"

Hospital DataExtractor::extraerDatos(const QList<Token>& tokens) {
    Hospital hospital;

    for (int i = 0; i < tokens.size(); ++i) {
        QString lexema = tokens[i].lexema.toLower();

        if (lexema == "paciente" && i + 2 < tokens.size() && tokens[i+1].tipo == DosPuntos) {
            Paciente p;
            p.nombre = tokens[i+2].lexema;
            p.nombre.remove("\""); 

            int j = i + 3;
            while (j < tokens.size() && tokens[j].tipo != CorcheteCierra && tokens[j].tipo != PuntoYComa) {
                QString atr = tokens[j].lexema.toLower();
                if (atr == "edad" && j + 2 < tokens.size()) p.edad = tokens[j+2].lexema.toInt();
                else if (atr == "tipo_sangre" && j + 2 < tokens.size()) {
                    p.tipo_sangre = tokens[j+2].lexema;
                    p.tipo_sangre.remove("\"");
                }
                else if (atr == "habitacion" && j + 2 < tokens.size()) p.habitacion = tokens[j+2].lexema.toInt();
                j++;
            }
            hospital.pacientes.append(p);
            i = j; 
        }

        else if (lexema == "medico" && i + 2 < tokens.size() && tokens[i+1].tipo == DosPuntos) {
            Medico m;
            m.nombre = tokens[i+2].lexema;
            m.nombre.remove("\"");

            int j = i + 3;
            while (j < tokens.size() && tokens[j].tipo != CorcheteCierra && tokens[j].tipo != PuntoYComa) {
                QString atr = tokens[j].lexema.toLower();
                if (atr == "especialidad" && j + 2 < tokens.size()) m.especialidad = tokens[j+2].lexema;
                else if (atr == "codigo" && j + 2 < tokens.size()) {
                    m.codigo = tokens[j+2].lexema;
                    m.codigo.remove("\"");
                }
                j++;
            }
            hospital.medicos.append(m);
            i = j;
        }

        else if (lexema == "cita" && i + 2 < tokens.size() && tokens[i+1].tipo == DosPuntos) {
            Cita c;
            c.paciente = tokens[i+2].lexema;
            c.paciente.remove("\"");

            int j = i + 3;
            while (j < tokens.size() && tokens[j].lexema.toLower() != "con" && tokens[j].tipo != CorcheteAbre) j++;
            
            if (j + 1 < tokens.size() && tokens[j].lexema.toLower() == "con") {
                c.medico = tokens[j+1].lexema;
                c.medico.remove("\"");
            }

            while (j < tokens.size() && tokens[j].tipo != CorcheteCierra && tokens[j].tipo != PuntoYComa) {
                QString atr = tokens[j].lexema.toLower();
                if (atr == "fecha" && j + 2 < tokens.size()) c.fecha = tokens[j+2].lexema;
                else if (atr == "hora" && j + 2 < tokens.size()) c.hora = tokens[j+2].lexema;
                j++;
            }
            hospital.citas.append(c);
            i = j;
        }

        else if (lexema == "diagnostico" && i + 2 < tokens.size() && tokens[i+1].tipo == DosPuntos) {
            QString nombrePac = tokens[i+2].lexema;
            nombrePac.remove("\"");

            Diagnostico d;
            int j = i + 3;
            while (j < tokens.size() && tokens[j].tipo != CorcheteCierra && tokens[j].tipo != PuntoYComa) {
                QString atr = tokens[j].lexema.toLower();
                if (atr == "condicion" && j + 2 < tokens.size()) { d.condicion = tokens[j+2].lexema; d.condicion.remove("\""); }
                else if (atr == "medicamento" && j + 2 < tokens.size()) { d.medicamento = tokens[j+2].lexema; d.medicamento.remove("\""); }
                else if (atr == "dosis" && j + 2 < tokens.size()) { d.dosis = tokens[j+2].lexema; d.dosis.remove("\""); }
                j++;
            }

            for (int k = 0; k < hospital.pacientes.size(); k++) {
                if (hospital.pacientes[k].nombre == nombrePac) {
                    hospital.pacientes[k].tiene_diagnostico = true;
                    hospital.pacientes[k].diagnostico = d;
                    break;
                }
            }
            i = j;
        }
    }

    return hospital;
}