#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

void leerArchivo(const string & nombreArchivo);

void mostrarMenu(){
    cout << "BIENVENIDO AL MENU DE INVENTARIO"<< endl;
    cout << "1. Leer archivo .inv e imprimir su contenido"<< endl;
    cout << "2. Salir del programa"<< endl;
    cout << "Seleccione su opcion: "<< endl;
}

int main(){
    int opc;
    string archivo="inventario.inv";
    do{
        mostrarMenu();
        cin>>opc;
        try{
            switch(opc){
                case 1:
                    cout << "Mostrando información del archivo"<< endl;
                    leerArchivo(archivo);
                    break;
                case 2:
                    cout << "Saliendo del programa";
                    break;
                default:
                    cout<<"Error, opcion incorrecta"<< endl;
            }
        } catch (const exception& e){
            cout << "Error" << e.what() << endl;
        }
    } while (opc != 2);
    return 0;
}

void leerArchivo(const string& nombreArchivo){
    ifstream archivo(nombreArchivo);
    string linea;

    if(!archivo.is_open()){
        throw runtime_error("Error al abrir el archivo");
    }
    cout << "Mostrando archivo:";
    while (getline(archivo, linea)){
        cout << linea << endl;
    }
    archivo.close();
}