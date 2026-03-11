#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//escribir solo números para aceptar la cadena como entero
bool esEntero(string s)
{
    int estado = 0;

    for(int i = 0; i < s.length(); i++)
    {
        char c = s[i];

        if(estado == 0)
        {
            if(c >= '0' && c <= '9')
                estado = 1;
            else
                return false;
        }
        else if(estado == 1)
        {
            if(c >= '0' && c <= '9')
                estado = 1;
            else
                return false;
        }
    }

    return estado == 1;
}

//escribir tres letras mayúsculas, un guión, y tres números para aceptar la cadena como código
bool esCodigo(string s)
{
    int estado = 0;

    for(int i = 0; i < s.length(); i++)
    {
        char c = s[i];

        switch(estado)
        {
            case 0:
                if(c >= 'A' && c <= 'Z') estado = 1;
                else return false;
                break;

            case 1:
                if(c >= 'A' && c <= 'Z') estado = 2;
                else return false;
                break;

            case 2:
                if(c >= 'A' && c <= 'Z') estado = 3;
                else return false;
                break;

            case 3:
                if(c == '-') estado = 4;
                else return false;
                break;

            case 4:
                if(c >= '0' && c <= '9') estado = 5;
                else return false;
                break;

            case 5:
                if(c >= '0' && c <= '9') estado = 5;
                else return false;
                break;
        }
    }

    return estado == 5;
}

//crear gráfica 
void generarDiagramas()
{
    ofstream entero("afd_entero.dot");

    entero << "digraph AFD_Entero {\n";
    entero << "rankdir=LR;\n";
    entero << "node [shape = doublecircle]; q1;\n";
    entero << "node [shape = circle];\n";
    entero << "q0 -> q1 [label=\"0-9\"];\n";
    entero << "q1 -> q1 [label=\"0-9\"];\n";
    entero << "}\n";

    entero.close();


    ofstream codigo("afd_codigo.dot");

    codigo << "digraph AFD_Codigo {\n";
    codigo << "rankdir=LR;\n";
    codigo << "node [shape = doublecircle]; q5;\n";
    codigo << "node [shape = circle];\n";
    codigo << "q0 -> q1 [label=\"A-Z\"];\n";
    codigo << "q1 -> q2 [label=\"A-Z\"];\n";
    codigo << "q2 -> q3 [label=\"A-Z\"];\n";
    codigo << "q3 -> q4 [label=\"-\"];\n";
    codigo << "q4 -> q5 [label=\"0-9\"];\n";
    codigo << "q5 -> q5 [label=\"0-9\"];\n";
    codigo << "}\n";

    codigo.close();
}

void generarImagenes()
{
    system("dot -Tpng afd_entero.dot -o afd_entero.png");
    system("dot -Tpng afd_codigo.dot -o afd_codigo.png");
}

int main()
{
    generarDiagramas();
    generarImagenes();
    string cadena;
    char continuar;

    do
    {
        cout << "Ingrese una cadena: ";
        cin >> cadena;

        if(esEntero(cadena))
            cout << "Cadena valida como entero";
        else if(esCodigo(cadena))
            cout << "Cadena valida como codigo";
        else
            cout << "Cadena rechazada";

        cout << "\nDesea probar otra cadena? (s/n): ";
        cin >> continuar;

    } while(continuar == 's' || continuar == 'S');

    cout << "Fin del programa";

    return 0;
}