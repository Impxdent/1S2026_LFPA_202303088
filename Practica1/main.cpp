#include <iostream>

using namespace std;

int main(){
    int opc = 0;
    do{
        cout << "=========================================" << endl;
        cout << "     SISTEMA DE ANALISIS ACADEMICO" << endl;
        cout << "=========================================" << endl;
        cout << "1. Cargar archivo de estudiantes" << endl;
        cout << "2. Cargar archivo de cursos" << endl;
        cout << "3. Cargar archivo de notas" << endl;
        cout << "4. Generar reporte: Estadisticas por curso" << endl;
        cout << "5. Generar reporte: Rendimiento por estudiante" << endl;
        cout << "6. Generar reporte: Top 10 mejores estudiantes" << endl;
        cout << "7. Generar reporte: Cursos con mayor reprobación" << endl;
        cout << "8. Generar reporte: Analisis por carrera" << endl;
        cout << "9. Salir" << endl;
        cout << "Seleccione una opcion: " << endl;
        cin >> opc;

        switch(opc){
            case 1:
                cout << "Cargar archivo de estudiantes" << endl;
                break;
            case 2:
                cout << "Cargar cursos" << endl;
                break;
            case 3:
                cout << "Cargar notas" << endl;
                break;
            case 4:
                cout << "Reporte por curso" << endl;
                break;
            case 5:
                cout << "Rendimiento por estudiante" << endl;
                break;
            case 6:
                cout << "Top 10 estudiantes" << endl;
                break;
            case 7:
                cout << "Cursos con mayor reprobación" << endl;
                break;
            case 8:
                cout << "Analisis por carrera" << endl;
                break;
            case 9:
                cout << "Fin del programa" << endl;
                break;
            default:
                cout << "Error, ingrese opcion valida" << endl;
                break;
        }
    } 
    while (opc!=9);
    return 0;
}