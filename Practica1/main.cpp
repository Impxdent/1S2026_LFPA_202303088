#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct Estudiante{
    int carnet;
    string nombre;
    string apellido;
    string carrera;
    int semestre;
};

Estudiante*estudiantes=nullptr;
int totalEstudiantes=0;
int capacidadEstudiantes=0;

void inicializarEstudiantes(int capacidad);
void agregarEstudiantes(const Estudiante & e);
void cargarEstudiantes();

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
                cargarEstudiantes();
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
                cout << "Cursos con mayor reprobacion" << endl;
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
    delete[] estudiantes;
    return 0;
}

void inicializarEstudiantes(int capacidad){
    capacidadEstudiantes=capacidad;
    totalEstudiantes=0;
    estudiantes=new Estudiante[capacidadEstudiantes];
}

void agregarEstudiantes(const Estudiante& e){
    if (totalEstudiantes<capacidadEstudiantes){
        estudiantes[totalEstudiantes++]=e;
    } else {
        cout<<"Capacidad maxima alcanzada"<<endl;
    }
}

void cargarEstudiantes(){
    ifstream archivo("estudiantes.lfp");
    string linea;

    if (!archivo.is_open()){
        cout<<"Error al abrir el archivo"<<endl;
        return;
    }
    inicializarEstudiantes(100);

    while (getline(archivo, linea)){
        Estudiante e;
        string token;
        stringstream ss(linea);

        getline(ss, token, ',');
        e.carnet=stoi(token);
        getline(ss, e.nombre,',');
        getline(ss, e.apellido,',');
        getline(ss, e.carrera,',');
        getline(ss, token, ',');
        e.semestre=stoi(token);

        agregarEstudiantes(e);
    }
    archivo.close();
    cout<<"Los estudiantes se ingresaron correctamente"<<endl;

    for (int i = 0; i < totalEstudiantes; i++) {
        cout << estudiantes[i].carnet << " , "
             << estudiantes[i].nombre << " , "
             << estudiantes[i].apellido << " , "
             << estudiantes[i].carrera << " , "
             << estudiantes[i].semestre << endl;
    }
}