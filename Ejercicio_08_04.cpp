// Materia: Programación I, Paralelo 4
// Autor: Andres Ignacio Pabon Sotomayor
// Fecha creación: 26/11/2023
// Fecha modificación: 27/11/2023
// Número de ejericio: 4
// Problema planteado: Codifique un programa que cree un fichero para contener los datos relativos a los artículos de un almacén.
// Para cada artículo habrá de guardar la siguiente información: 
// • Código del artículo (Numérico) 
// • Nombre del artículo (Cadena de caracteres) 
// • Existencias actuales (Numérico) 
// • Precio (Numérico decimal). 
// Se deberán pedir datos de cada artículo por teclado hasta que como código se teclee el código 0.
// El fichero se habrá de crear ordenado por el código del artículo. 

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const char* NOMBRE_ARCHIVO_ALMACEN = "almacen.dat";

struct Articulo
{
    int codigo;
    char nombre[50];
    int stock;
    double precio;
};

bool compararPorCodigo(const Articulo& a, const Articulo& b)
{
    return a.codigo < b.codigo;
}

void escribirArchivoBinario(const vector<Articulo>& articulos)
{
    ofstream archivoEscritura;
    archivoEscritura.open(NOMBRE_ARCHIVO_ALMACEN, ios::binary);

    if (!archivoEscritura.is_open())
    {
        cout << "No se pudo abrir el archivo para escritura." << endl;
        return;
    }

    for (const Articulo& articulo : articulos)
    {
        archivoEscritura.write(reinterpret_cast<const char*>(&articulo), sizeof(Articulo));
    }

    archivoEscritura.close();
}

int main()
{
    vector<Articulo> articulos;

    while (true)
    {
        Articulo nuevoArticulo;

        // Ingresar información del artículo
        cout << "Ingrese el código del artículo (0 para finalizar): ";
        cin >> nuevoArticulo.codigo;

        if (nuevoArticulo.codigo == 0)
            break;

        cin.ignore(); // Limpiar el buffer después de leer el código

        cout << "Ingrese el nombre del artículo: ";
        cin.getline(nuevoArticulo.nombre, 50);

        cout << "Ingrese el stock actual: ";
        cin >> nuevoArticulo.stock;

        cout << "Ingrese el precio: ";
        cin >> nuevoArticulo.precio;

        // Agregar el nuevo artículo al vector
        articulos.push_back(nuevoArticulo);
    }

    // Ordenar el vector por código antes de escribir en el archivo
    sort(articulos.begin(), articulos.end(), compararPorCodigo);

    // Escribir la información en el archivo
    escribirArchivoBinario(articulos);

    cout << "Proceso finalizado. Se ha creado el archivo 'almacen.dat'." << endl;

    return 0;
}


