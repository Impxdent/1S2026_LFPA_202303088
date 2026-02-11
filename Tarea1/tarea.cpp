#include <iostream>
using namespace std;

class Carro {
private: //atributos privados
    string marca;
    float motor;
    string color;

public: //constructor de atributoss
    Carro(string m, float mo, string c) {
        marca = m;
        motor = mo;
        color = c;
    }

    void mostrarInfo() { //método 1
        cout << "Informacion del carro:" << endl;
        cout << "Marca: " << marca << endl;
        cout << "Motor: " << motor << endl;
        cout << "Color: " << color << endl;
        cout << endl;
    }

    void acelerar(){ //método 2
        cout << "El carro " << marca << " esta acelerando (vroom, vroom)" << endl;
    }
};

int main() { //dos objetos
    Carro carro1("Toyota", 2.8, "Blanco");
    Carro carro2("Honda", 1.6, "Rojo");

    //prueba de métodos

    carro1.mostrarInfo();
    carro2.mostrarInfo();
    cout << endl;
    carro1.acelerar();
    cout << endl;
    carro2.acelerar();
    cout << endl;

    return 0;
}
