// Materia: Programación I, Paralelo 4
// Autor: Andres Ignacio Pabon Sotomayor
// Fecha creación: 26/11/2023
// Fecha modificación: 27/11/2023
// Número de ejericio: 7
// Problema planteado: Escriba un programa que tenga como entrada un fichero que contenga un texto
// y dé como resultado una estadística del número de palabras. 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

void generarEstadisticas(const string& nombreArchivo) {
    ifstream archivoEntrada(nombreArchivo);

    if (!archivoEntrada.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    map<string, int> estadisticas;
    string palabra;

    while (archivoEntrada >> palabra) {
        // Eliminar caracteres no alfabéticos al inicio y final de la palabra
        size_t inicio = palabra.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
        size_t fin = palabra.find_last_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");

        if (inicio != string::npos && fin != string::npos) {
            palabra = palabra.substr(inicio, fin - inicio + 1);
            estadisticas[palabra]++;
        }
    }

    archivoEntrada.close();

    // Mostrar estadísticas
    cout << "Estadísticas de palabras en el archivo '" << nombreArchivo << "':" << endl;
    for (const auto& par : estadisticas) {
        cout << par.first << ": " << par.second << " veces." << endl;
    }
}

int main() {
    string nombreArchivo;

    cout << "Ingrese el nombre del archivo: ";
    getline(cin, nombreArchivo);

    generarEstadisticas(nombreArchivo);

    return 0;
}

