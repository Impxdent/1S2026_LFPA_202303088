#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

//declaración de estructuras para datos

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

//arreglos dinámicos y contadores

Estudiante*estudiantes=nullptr;
int totalEstudiantes=0;
int capacidadEstudiantes=0;

Curso*cursos=nullptr;
int totalCursos=0;
int capacidadCursos=0;

Nota*notas=nullptr;
int totalNotas=0;
int capacidadNotas=0;

//función para eliminar espacios
string limpiar(string s){
    while(!s.empty() && isspace(s.front())) s.erase(s.begin());
    while(!s.empty() && isspace(s.back())) s.pop_back();
    return s;
}

//llamar métodos

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

void reporteEstadisticasPorCurso();

void reporteRendimientoEstudiante();

void reporteTop10Estudiantes();

void reporteCursosMayorReprobacion();

void reporteAnalisisPorCarrera();

//menú principal

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
                reporteEstadisticasPorCurso();
                break;
            case 5:
                reporteRendimientoEstudiante();
                break;
            case 6:
                reporteTop10Estudiantes();
                break;
            case 7:
                reporteCursosMayorReprobacion();
                break;
            case 8:
                reporteAnalisisPorCarrera();
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
    //limpiar campos
    delete[] estudiantes;
    delete[] cursos;
    delete[] notas;
    return 0;
}

//caso 1
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
    ifstream archivo("estudiantes.lfp"); //cargar el archivo
    string linea;

    if (!archivo.is_open()){
        cout<<"Error al abrir el archivo"<<endl;
        return;
    }
    inicializarEstudiantes(100);

    while (getline(archivo, linea)){ //leer datos
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

//caso2
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
        getline(ss, c.carrera, ',');

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

//caso3
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

//caso4
void reporteEstadisticasPorCurso(){
    ofstream html("ReporteEstadisticasCurso.html");
    if(!html.is_open()){
        cout<<"Error al crear el reporte";
        return;
    }
    html << "<html><head><title>Estadisticas por Curso</title></head><body>";
    html << "<h1>Reporte de Estadisticas por Curso</h1>";
    html << "<table border='1'>";
    html << "<tr>"
         << "<th>Codigo</th>"
         << "<th>Curso</th>"
         << "<th>Total Estudiantes</th>"
         << "<th>Promedio</th>"
         << "<th>Aprobados</th>"
         << "<th>Reprobados</th>"
         << "</tr>";

    for(int i = 0; i < totalCursos; i++){
        int contador = 0;
        float suma = 0;
        int aprobados = 0;
        int reprobados = 0;

        for(int j = 0; j < totalNotas; j++){
            if(notas[j].codigoCurso == cursos[i].codigo){
                contador++;
                suma += notas[j].nota;
                if(notas[j].nota >= 61)
                    aprobados++;
                else
                    reprobados++;
            }
        }     
        if(contador > 0){
            html << "<tr>";
            html << "<td>" << cursos[i].codigo << "</td>";
            html << "<td>" << cursos[i].nombre << "</td>";
            html << "<td>" << contador << "</td>";
            html << "<td>" << (suma / contador) << "</td>";
            html << "<td>" << aprobados << "</td>";
            html << "<td>" << reprobados << "</td>";
            html << "</tr>";
        }
    }

    html << "</table></body></html>";
    html.close();

    cout << "Reporte 4 generado: ReporteEstadisticasCurso.html";
}

//caso5
void reporteRendimientoEstudiante(){
    ofstream html("ReporteRendimientoEstudiante.html");

    if(!html.is_open()){
        cout << "Error al crear el reporte";
        return;
    }

    html << "<html><head><title>Rendimiento por Estudiante</title></head><body>";
    html << "<h1>Reporte de Rendimiento por Estudiante</h1>";
    html << "<table border='1'>";
    html << "<tr>"
         << "<th>Carnet</th>"
         << "<th>Nombre</th>"
         << "<th>Carrera</th>"
         << "<th>Semestre</th>"
         << "<th>Promedio</th>"
         << "<th>Aprobados</th>"
         << "<th>Reprobados</th>"
         << "</tr>";

    for(int i = 0; i < totalEstudiantes; i++){
        float suma = 0;
        int contador = 0;
        int aprobados = 0;
        int reprobados = 0;

        for(int j = 0; j < totalNotas; j++){
            if(notas[j].carnet == estudiantes[i].carnet){
                suma += notas[j].nota;
                contador++;
                if(notas[j].nota >= 61)
                    aprobados++;
                else
                    reprobados++;
            }
        }

        if(contador > 0){
            html << "<tr>";
            html << "<td>" << estudiantes[i].carnet << "</td>";
            html << "<td>" << estudiantes[i].nombre << " "
                 << estudiantes[i].apellido << "</td>";
            html << "<td>" << estudiantes[i].carrera << "</td>";
            html << "<td>" << estudiantes[i].semestre << "</td>";
            html << "<td>" << (suma / contador) << "</td>";
            html << "<td>" << aprobados << "</td>";
            html << "<td>" << reprobados << "</td>";
            html << "</tr>";
        }
    }

    html << "</table></body></html>";
    html.close();

    cout << "Reporte 5 generado: ReporteRendimientoEstudiante.html";
}

//caso6
void reporteTop10Estudiantes(){
    ofstream html("reporte_top10.html");

    if(!html.is_open()){
        cout << "Error al crear reporte";
        return;
    }

    float promedios[100];
    int indices[100];

    for(int i = 0; i < totalEstudiantes; i++){
        float suma = 0;
        int cont = 0;

        for(int j = 0; j < totalNotas; j++){
            if(notas[j].carnet == estudiantes[i].carnet){
                suma += notas[j].nota;
                cont++;
            }
        }

        if(cont > 0){
            promedios[i] = suma / cont;
            indices[i] = i;
        } else {
            promedios[i] = -1;
            indices[i] = i;
        }
    }

    for(int i = 0; i < totalEstudiantes - 1; i++){
        for(int j = i + 1; j < totalEstudiantes; j++){
            if(promedios[j] > promedios[i]){
                swap(promedios[i], promedios[j]);
                swap(indices[i], indices[j]);
            }
        }
    }

    html << "<html><body><h1>Top 10 Mejores Estudiantes</h1>";
    html << "<table border='1'>";
    html << "<tr><th>Posicion</th><th>Carnet</th><th>Nombre</th><th>Promedio</th></tr>";

    for(int i = 0; i < 10 && i < totalEstudiantes; i++){
        if(promedios[i] >= 0){
            int idx = indices[i];
            html << "<tr>";
            html << "<td>" << (i+1) << "</td>";
            html << "<td>" << estudiantes[idx].carnet << "</td>";
            html << "<td>" << estudiantes[idx].nombre << " "
                 << estudiantes[idx].apellido << "</td>";
            html << "<td>" << promedios[i] << "</td>";
            html << "</tr>";
        }
    }

    html << "</table></body></html>";
    html.close();

    cout << "Reporte Top 10 generado";
}

//caso7
void reporteCursosMayorReprobacion(){
    ofstream html("ReporteReprobacionCursos.html");

    if(!html.is_open()){
        cout << "Error al crear reporte de reprobacion";
        return;
    }

    html << "<html><body><h1>Cursos con Mayor Reprobacion</h1>";
    html << "<table border='1'>";
    html << "<tr>"
         << "<th>Codigo</th><th>Curso</th>"
         << "<th>Total</th><th>Aprobados</th>"
         << "<th>Reprobados</th><th>% Reprobacion</th>"
         << "</tr>";

    for(int i = 0; i < totalCursos; i++){
        int total = 0, aprob = 0, repro = 0;

        for(int j = 0; j < totalNotas; j++){
            if(notas[j].codigoCurso == cursos[i].codigo){
                total++;
                if(notas[j].nota >= 61)
                    aprob++;
                else
                    repro++;
            }
        }

        if(total > 0){
            float porcentaje = (repro * 100.0) / total;
            html << "<tr>";
            html << "<td>" << cursos[i].codigo << "</td>";
            html << "<td>" << cursos[i].nombre << "</td>";
            html << "<td>" << total << "</td>";
            html << "<td>" << aprob << "</td>";
            html << "<td>" << repro << "</td>";
            html << "<td>" << porcentaje << "%</td>";
            html << "</tr>";
        }
    }

    html << "</table></body></html>";
    html.close();

    cout << "Reporte de cursos con mayor reprobacion generado";
}

//caso8
void reporteAnalisisPorCarrera(){
    ofstream html("ReporteAnalisisCarrera.html");

    if(!html.is_open()){
        cout << "Error al crear reporte por carrera";
        return;
    }

    html << "<html><body><h1>Analisis por Carrera</h1>";
    html << "<table border='1'>";
    html << "<tr>"
         << "<th>Carrera</th>"
         << "<th>Total Estudiantes</th>"
         << "<th>Promedio General</th>"
         << "</tr>";

    for(int i = 0; i < totalEstudiantes; i++){
        string carrera = estudiantes[i].carrera;
        bool procesada = false;

        for(int k = 0; k < i; k++){
            if(estudiantes[k].carrera == carrera){
                procesada = true;
                break;
            }
        }
        if(procesada) continue;

        int totalEst = 0;
        float sumaNotas = 0;
        int totalNotasCarrera = 0;

        for(int j = 0; j < totalEstudiantes; j++){
            if(estudiantes[j].carrera == carrera){
                totalEst++;
                for(int n = 0; n < totalNotas; n++){
                    if(notas[n].carnet == estudiantes[j].carnet){
                        sumaNotas += notas[n].nota;
                        totalNotasCarrera++;
                    }
                }
            }
        }

        float promedio = (totalNotasCarrera > 0)
                         ? sumaNotas / totalNotasCarrera
                         : 0;

        html << "<tr>";
        html << "<td>" << carrera << "</td>";
        html << "<td>" << totalEst << "</td>";
        html << "<td>" << promedio << "</td>";
        html << "</tr>";
    }

    html << "</table></body></html>";
    html.close();

    cout << "Reporte de analisis por carrera generado";
}