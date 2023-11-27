// Materia: Programaci�n I, Paralelo 4
// Autor: Andres Ignacio Pabon Sotomayor
// Fecha creaci�n: 26/11/2023
// Fecha modificaci�n: 27/11/2023
// N�mero de ejericio: 3
// Problema planteado: Ampl�e el programa anterior que procesa clientes de una agencia matrimonial 
// para que tome los datos de todos los candidatos a estudiar del fichero PERSONAS.DAT del ejercicio anterior,
// lea el cliente del teclado y finalmente genere como resultado un listado por pantalla con los nombres de los candidatos aceptados
// y un fichero llamado ACEPTADOS.DAT con toda la informaci�n correspondiente a los candidatos aceptados. 
// Una persona del fichero PERSONAS.DAT se considerar� aceptable como candidato si tiene diferente sexo y que haya nacido en el mes y a�o 
// (El programa debe ser capaz de trabajar con cualquier n�mero de personas en el fichero PERSONAS.DAT).

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const char* ARCHIVO_PERSONAS = "PERSONAS.BIN";

struct DatosPersona
{
    char nombre[31];
    int edad;
    char genero;
    char fechaNacimiento[11];
};

void guardarDatosBinarios(const DatosPersona& persona)
{
    ofstream archivoGuardar;
    archivoGuardar.open(ARCHIVO_PERSONAS, ios::app | ios::binary);
    archivoGuardar.write(reinterpret_cast<const char*>(&persona), sizeof(DatosPersona));
    archivoGuardar.close();
}

int main()
{
    DatosPersona persona;

    while (true)
    {
        // Ingresar informaci�n de la persona
        cout << "Ingrese el nombre (o espacio para finalizar): ";
        cin.getline(persona.nombre, 31);

        // Verificar si se debe finalizar el programa
        if (strlen(persona.nombre) == 0 || persona.nombre[0] == ' ')
            break;

        cout << "Ingrese la edad: ";
        cin >> persona.edad;

        cout << "Ingrese el g�nero (M/F): ";
        cin >> persona.genero;

        cout << "Ingrese la fecha de nacimiento (dd/mm/yyyy): ";
        cin >> persona.fechaNacimiento;

        // Limpiar el buffer despu�s de leer el g�nero
        cin.ignore();

        // Escribir la informaci�n en el archivo binario
        guardarDatosBinarios(persona);
    }

    cout << "Proceso finalizado. Se ha creado el archivo 'PERSONAS.BIN'." << endl;

    return 0;
}

