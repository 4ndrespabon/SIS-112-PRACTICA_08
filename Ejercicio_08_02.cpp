// Materia: Programaci�n I, Paralelo 4
// Autor: Andres Ignacio Pabon Sotomayor
// Fecha creaci�n: 26/11/2023
// Fecha modificaci�n: 27/11/2023
// N�mero de ejericio: 2
// Problema planteado:Escriba un programa que cree un fichero de texto llamado "PERSONAS.BIN" en el que se
//guarde la informaci�n de un n�mero indeterminado de personas.
//La informaci�n que se guardar� por cada persona ser�:
//� Nombre: De 1 a 30 caracteres.
//� Edad num�rico (>= 1 y <=100)
//� Sexo CHAR (M/F).
//� FechaNacimiento CHAR(10) (formato dd/mm/yyyy)
//La informaci�n correspondiente a cada persona se leer� del teclado.
//El proceso finalizar� cuando se teclee un campo "Nombre" que est� solamente con el car�cter de espacio.
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

