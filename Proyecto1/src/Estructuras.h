#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <QString>
#include <QList>

struct Diagnostico {
    QString condicion;
    QString medicamento;
    QString dosis;
};

struct Paciente {
    QString nombre;
    int edad = 0;
    QString tipo_sangre;
    int habitacion = 0;
    
    bool tiene_diagnostico = false;
    Diagnostico diagnostico;
};

struct Medico {
    QString nombre;
    QString codigo;
    QString especialidad;
    
    int citas_programadas = 0;
    QList<QString> pacientes_atendidos; 
};

struct Cita {
    QString paciente;
    QString medico;
    QString fecha;
    QString hora;
    
    bool tiene_conflicto = false;
};

struct Hospital {
    QList<Paciente> pacientes;
    QList<Medico> medicos;
    QList<Cita> citas;
};

#endif 