// Materia: Programación I, Paralelo 4
// Autor: Andres Ignacio Pabon Sotomayor
// Fecha creación: 26/11/2023
// Fecha modificación: 27/11/2023
// Número de ejericio: 
// Problema planteado: Escribir un programa con la opción de encriptar y de desencriptar un fichero de texto. 
// La encriptación consiste en que dado un fichero de texto de entrada genere otro fichero de salida de extensión <nombre>.
// COD donde el texto estará codificado (encriptado). 
// Esta codificación consiste en reemplazar cada carácter por el tercero siguiente según la tabla ASCII.  
// La opción de desencriptado consiste en leer un fichero <nombre>.COD y recuperar la información original.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void encriptarArchivo(const string &nombreEntrada, const string &nombreSalida);
void desencriptarArchivo(const string &nombreEntrada, const string &nombreSalida);

int main() {
    string nombreArchivo;
    cout << "Ingrese el nombre del archivo: ";
    getline(cin, nombreArchivo);

    // Encriptar el archivo
    encriptarArchivo(nombreArchivo, nombreArchivo + ".COD");

    // Desencriptar el archivo
    desencriptarArchivo(nombreArchivo + ".COD", nombreArchivo + "_desencriptado.txt");

    return 0;
}

void encriptarArchivo(const string &nombreEntrada, const string &nombreSalida) {
    ifstream archivoEntrada(nombreEntrada);
    ofstream archivoSalida(nombreSalida);

    if (!archivoEntrada.is_open() || !archivoSalida.is_open()) {
        cout << "Error al abrir los archivos." << endl;
        return;
    }

    char caracter;
    while (archivoEntrada.get(caracter)) {
        // Encriptar: reemplazar cada carácter por el tercero siguiente en la tabla ASCII
        caracter = caracter + 3;
        archivoSalida.put(caracter);
    }

    archivoEntrada.close();
    archivoSalida.close();

    cout << "Encriptación completada. Archivo encriptado: " << nombreSalida << endl;
}

void desencriptarArchivo(const string &nombreEntrada, const string &nombreSalida) {
    ifstream archivoEntrada(nombreEntrada);
    ofstream archivoSalida(nombreSalida);

    if (!archivoEntrada.is_open() || !archivoSalida.is_open()) {
        cout << "Error al abrir los archivos." << endl;
        return;
    }

    char caracter;
    while (archivoEntrada.get(caracter)) {
        // Desencriptar: reemplazar cada carácter por el tercero anterior en la tabla ASCII
        caracter = caracter - 3;
        archivoSalida.put(caracter);
    }

    archivoEntrada.close();
    archivoSalida.close();

    cout << "Desencriptación completada. Archivo desencriptado: " << nombreSalida << endl;
}

