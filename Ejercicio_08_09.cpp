// Materia: Programación I, Paralelo 4
// Autor: Andres Ignacio Pabon Sotomayor
// Fecha creación: 26/11/2023
// Fecha modificación: 30/11/2023
// Número de ejericio: 9
// Problema planteado: Dado una tabla grabada en un fichero en formato binario <nombre>.BIN hallar la suma
// horizontal y vertical y grabar la tabla y los resultados en otro fichero de texto o binario según se
// introduzca por pantalla.

#include <iostream>
#include <fstream>
#include <iomanip>

const char* NOMBRE_ARCHIVO_BIN = "FICHEROBINARIO.bin";
const char* NOMBRE_ARCHIVO_TXT = "RESULTADOS.txt";

void introducirTabla(const char* NOMBRE_ARCHIVO_BIN);
void calcularSumas(const char* NOMBRE_ARCHIVO_TXT);

int main() {
    introducirTabla(NOMBRE_ARCHIVO_BIN);
    calcularSumas(NOMBRE_ARCHIVO_TXT);
    return 0;
}

void introducirTabla(const char* NOMBRE_ARCHIVO_BIN) {
    int numFilas, numColumnas;
    std::cout << "Ingrese la cantidad de filas para su archivo: ";
    std::cin >> numFilas;
    std::cout << "Ingrese la cantidad de columnas para su archivo: ";
    std::cin >> numColumnas;

    double matriz[numFilas][numColumnas];

    std::ofstream archivoBinario(NOMBRE_ARCHIVO_BIN, std::ios::binary);
    if (!archivoBinario.is_open()) {
        std::cerr << "Error al abrir el archivo binario para escritura." << std::endl;
        return;
    }

    archivoBinario.write(reinterpret_cast<const char*>(&numFilas), sizeof(numFilas));
    archivoBinario.write(reinterpret_cast<const char*>(&numColumnas), sizeof(numColumnas));

    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numColumnas; j++) {
            std::cout << "Ingrese el número decimal para la fila " << i + 1 << " y columna " << j + 1 << ": ";
            std::cin >> matriz[i][j];
            archivoBinario.write(reinterpret_cast<const char*>(&matriz[i][j]), sizeof(matriz[i][j]));
        }
    }

    archivoBinario.close();
    std::cout << "Se ha completado la escritura en el archivo binario." << std::endl;
}

void calcularSumas(const char* NOMBRE_ARCHIVO_TXT) {
    std::ifstream archivoBinario(NOMBRE_ARCHIVO_BIN, std::ios::binary);

    if (!archivoBinario.is_open()) {
        std::cerr << "Error al abrir el archivo binario para lectura." << std::endl;
        return;
    }

    int numFilas, numColumnas;
    archivoBinario.read(reinterpret_cast<char*>(&numFilas), sizeof(numFilas));
    archivoBinario.read(reinterpret_cast<char*>(&numColumnas), sizeof(numColumnas));

    double matriz[numFilas][numColumnas];

    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numColumnas; j++) {
            archivoBinario.read(reinterpret_cast<char*>(&matriz[i][j]), sizeof(matriz[i][j]));
        }
    }

    archivoBinario.close();

    double sumasFilas[numFilas] = {0.0};
    double sumasColumnas[numColumnas] = {0.0};

    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numColumnas; j++) {
            sumasFilas[i] += matriz[i][j];
            sumasColumnas[j] += matriz[i][j];
        }
    }

    std::ofstream archivoTexto(NOMBRE_ARCHIVO_TXT);
    if (!archivoTexto.is_open()) {
        std::cerr << "Error al abrir el archivo de texto para escritura." << std::endl;
        return;
    }

    for (int i = 0; i < numFilas; i++) {
        for (int j = 0; j < numColumnas; j++) {
            archivoTexto << std::fixed << std::setprecision(2) << std::setw(7) << matriz[i][j] << " ";
        }

        double sumaFila = 0.0;
        for (int j = 0; j < numColumnas; j++) {
            sumaFila += matriz[i][j];
        }
        archivoTexto << "  Suma fila " << i + 1 << ": " << std::fixed << std::setprecision(2) << sumaFila << std::endl;
    }

    for (int j = 0; j < numColumnas; j++) {
        archivoTexto << "-------";
    }
    archivoTexto << std::endl;

    for (int j = 0; j < numColumnas; j++) {
        double sumaColumna = 0.0;
        for (int i = 0; i < numFilas; i++) {
            sumaColumna += matriz[i][j];
        }
        archivoTexto << std::fixed << std::setprecision(2) << std::setw(7) << sumaColumna << " ";
    }

    double sumaTotalColumnas = 0.0;
    for (int j = 0; j < numColumnas; j++) {
        sumaTotalColumnas += sumasColumnas[j];
    }
    archivoTexto << "                 : " << std::fixed << std::setprecision(2) << sumaTotalColumnas << std::endl;

    archivoTexto.close();
    std::cout << "Resultados escritos en el archivo de texto." << std::endl;
}

