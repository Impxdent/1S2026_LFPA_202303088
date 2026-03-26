#include "LexicalAnalyzer.h"

LexicalAnalyzer::LexicalAnalyzer() {}

QList<Token> LexicalAnalyzer::analizar(const QString& entrada) {
    QList<Token> listaTokens;
    int fila = 1;
    int columna = 1;
    int i = 0;
    int longitud = entrada.length();

    while (i < longitud) {
        QChar c = entrada[i];

        if (c.isSpace()) {
            if (c == '\n') {
                fila++;
                columna = 1;
            } else {
                columna++;
            }
            i++;
            continue;
        }

        if (c == '{') { listaTokens.append({LlaveAbre, "{", fila, columna}); i++; columna++; continue; }
        if (c == '}') { listaTokens.append({LlaveCierra, "}", fila, columna}); i++; columna++; continue; }
        if (c == '[') { listaTokens.append({CorcheteAbre, "[", fila, columna}); i++; columna++; continue; }
        if (c == ']') { listaTokens.append({CorcheteCierra, "]", fila, columna}); i++; columna++; continue; }
        if (c == ':') { listaTokens.append({DosPuntos, ":", fila, columna}); i++; columna++; continue; }
        if (c == ',') { listaTokens.append({Coma, ",", fila, columna}); i++; columna++; continue; }

        if (c == '"') {
            QString lexema = "\"";
            int colInicio = columna;
            i++; columna++;
            bool cerrada = false;

            while (i < longitud) {
                c = entrada[i];
                lexema += c;
                i++; columna++;
                if (c == '"') {
                    cerrada = true;
                    break;
                }
                if (c == '\n') { fila++; columna = 1; }
            }

            if (cerrada) {
                listaTokens.append({Cadena, lexema, fila, colInicio});
            } else {
                listaTokens.append({ErrorLexico, lexema, fila, colInicio}); 
            }
            continue;
        }

        if (c.isDigit()) {
            QString lexema = "";
            int colInicio = columna;
            
            while (i < longitud && (entrada[i].isDigit() || entrada[i] == '-' || entrada[i] == ':')) {
                lexema += entrada[i];
                i++; columna++;
            }

            if (lexema.contains("-")) {
                listaTokens.append({Fecha, lexema, fila, colInicio});
            } else if (lexema.contains(":")) {
                listaTokens.append({Hora, lexema, fila, colInicio});
            } else {
                listaTokens.append({Numero, lexema, fila, colInicio});
            }
            continue;
        }

        if (c.isLetter() || c == '_') {
            QString lexema = "";
            int colInicio = columna;
            
            while (i < longitud && (entrada[i].isLetterOrNumber() || entrada[i] == '_' || entrada[i] == '+')) {
                lexema += entrada[i];
                i++; columna++;
            }
            
            if (lexema == "HOSPITAL" || lexema == "paciente" || lexema == "edad" || 
                lexema == "tipo_sangre" || lexema == "fecha" || lexema == "hora" || 
                lexema == "medico" || lexema == "especialidad" || lexema == "codigo") {
                listaTokens.append({PalabraReservada, lexema, fila, colInicio});
            } else {
                listaTokens.append({Identificador, lexema, fila, colInicio});
            }
            continue;
        }
        listaTokens.append({ErrorLexico, QString(c), fila, columna});
        i++; columna++;
    }

    return listaTokens;
}