// Materia: Programación I, Paralelo 4
// Autor: Andres Ignacio Pabon Sotomayor
// Fecha creación: 26/11/2023
// Fecha modificación: 27/11/2023
// Número de ejericio: 8
// Problema planteado: Escribir un programa que genere a partir de un fichero de entrada 
// que contiene una tabla de números reales otro fichero de salida <nombre>.BIN grabado en formato binario.  
// Ej:  1.23  3.45  12.5  
//      4.8   3.9   0.83 ........................ 

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void crearArchivoBinario(const string& nombreArchivoEntrada, const string& nombreArchivoSalida) {
    ifstream archivoEntrada(nombreArchivoEntrada);
    if (!archivoEntrada.is_open()) {
        cout << "No se pudo abrir el archivo de entrada." << endl;
        return;
    }

    ofstream archivoSalida(nombreArchivoSalida, ios::binary);
    if (!archivoSalida.is_open()) {
        cout << "No se pudo abrir el archivo de salida." << endl;
        archivoEntrada.close();
        return;
    }

    double numero;
    while (archivoEntrada >> numero) {
        archivoSalida.write(reinterpret_cast<const char*>(&numero), sizeof(double));
    }

    archivoEntrada.close();
    archivoSalida.close();
    cout << "Proceso finalizado. Se ha creado el archivo '" << nombreArchivoSalida << "'." << endl;
}

int main() {
    string nombreArchivoEntrada, nombreArchivoSalida;

    cout << "Ingrese el nombre del archivo de entrada: ";
    getline(cin, nombreArchivoEntrada);

    cout << "Ingrese el nombre del archivo de salida (con extensión .BIN): ";
    getline(cin, nombreArchivoSalida);

    crearArchivoBinario(nombreArchivoEntrada, nombreArchivoSalida);

    return 0;
}


