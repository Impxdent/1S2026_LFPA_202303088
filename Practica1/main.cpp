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

struct Curso{
    int codigo;
    string nombre;
    int creditos;
    int semestre;
    string carrera;
};

struct Nota{
    int carnet;
    int codigoCurso;
    float nota;
    string ciclo;
    int año;
};

Estudiante*estudiantes=nullptr;
int totalEstudiantes=0;
int capacidadEstudiantes=0;

Curso*cursos=nullptr;
int totalCursos=0;
int capacidadCursos=0;

Nota*notas=nullptr;
int totalNotas=0;
int capacidadNotas=0;

void inicializarEstudiantes(int capacidad);
void agregarEstudiantes(const Estudiante & e);
void cargarEstudiantes();

void inicializarCursos(int capacidad);
void agregarCurso(const Curso& c);
void cargarCursos();

void inicializarNotas(int capacidad);
void agregarNota(const Nota& n);
void cargarNotas();

int buscarEstudiantePorCarnet(int carnet);

int buscarCursoPorCodigo(int codigo);

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
                cargarCursos();
                break;
            case 3:
                cargarNotas();
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
    delete[] cursos;
    delete[] notas;
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
    cout<<"Los estudiantes se cargaron correctamente"<<endl;

    for (int i = 0; i < totalEstudiantes; i++) {
        cout << estudiantes[i].carnet << " , "
             << estudiantes[i].nombre << " , "
             << estudiantes[i].apellido << " , "
             << estudiantes[i].carrera << " , "
             << estudiantes[i].semestre << endl;
    }
}

void inicializarCursos(int capacidad){
    capacidadCursos=capacidad;
    totalCursos=0;
    cursos=new Curso[capacidadCursos];
}

void agregarCurso(const Curso& c){
    if (totalCursos<capacidadCursos){
        cursos[totalCursos++]=c;
    } else {
        cout<<"Capacidad maxima alcanzada"<<endl;
    }
}

void cargarCursos(){
    ifstream archivo("cursos.lfp");
    string linea;

    if (!archivo.is_open()){
        cout<<"Error al abrir el archivo"<<endl;
        return;
    }
    inicializarCursos(100);

    while (getline(archivo, linea)){
        Curso c;
        string token;
        stringstream ss(linea);

        getline(ss, token, ',');
        c.codigo=stoi(token);
        getline(ss, c.nombre,',');
        getline(ss, token, ',');
        c.creditos=stoi(token);
        getline(ss, token, ',');
        c.semestre=stoi(token);
        getline(ss, token, ',');
        c.carrera=stoi(token);

        agregarCurso(c);
    }
    archivo.close();
    cout<<"Los cursos se cargaron correctamente"<<endl;

    for (int i = 0; i < totalCursos; i++) {
        cout << cursos[i].codigo << " , "
             << cursos[i].nombre << " , "
             << cursos[i].creditos << " , "
             << cursos[i].semestre << " , "
             << cursos[i].carrera << endl;
    }
}

void inicializarNotas(int capacidad){
    capacidadNotas=capacidad;
    totalNotas=0;
    notas=new Nota[capacidadNotas];
}

void agregarNota(const Nota& n){
    if (totalNotas<capacidadNotas){
        notas[totalNotas++]=n;
    } else {
        cout<<"Capacidad maxima alcanzada"<<endl;
    }
}

void cargarNotas(){
    ifstream archivo("notas.lfp");
    string linea;

    if (!archivo.is_open()){
        cout<<"Error al abrir el archivo"<<endl;
        return;
    }
    inicializarNotas(100);

    while (getline(archivo, linea)){
        Nota n;
        string token;
        stringstream ss(linea);

        getline(ss, token, ',');
        n.carnet=stoi(token);
        getline(ss, token, ',');
        n.codigoCurso=stoi(token);
        getline(ss, token, ',');
        n.nota=stof(token);
        getline(ss, n.ciclo, ',');
        getline(ss, token, ',');
        n.año=stoi(token);

        agregarNota(n);
    }
    archivo.close();
    cout<<"Las notas se cargaron correctamente"<<endl;

    for (int i = 0; i < totalNotas; i++) {
        cout << notas[i].carnet << " , "
             << notas[i].codigoCurso << " , "
             << notas[i].nota << " , "
             << notas[i].ciclo << " , "
             << notas[i].año << endl;
    }
}

int buscarEstudiantePorCarnet(int carnet){
    for (int i=0; i<totalEstudiantes; i++){
        if (estudiantes[i].carnet == carnet){
            return i;
        }
    }
    return -1;
}

int buscarCursoPorCodigo(int codigo){
    for (int i=0; i<totalCursos; i++){
        if (cursos[i].codigo == codigo){
            return i;
        }
    }
    return -1;
}