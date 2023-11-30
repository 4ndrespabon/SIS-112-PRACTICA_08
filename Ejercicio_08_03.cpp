// Materia: Programación I, Paralelo 4
// Autor: Andres Ignacio Pabon Sotomayor
// Fecha creación: 26/11/2023
// Fecha modificación: 27/11/2023
// Número de ejericio: 3
// Problema planteado: Amplíe el programa anterior que procesa clientes de una agencia matrimonial 
// para que tome los datos de todos los candidatos a estudiar del fichero PERSONAS.DAT del ejercicio anterior,
// lea el cliente del teclado y finalmente genere como resultado un listado por pantalla con los nombres de los candidatos aceptados
// y un fichero llamado ACEPTADOS.DAT con toda la información correspondiente a los candidatos aceptados. 
// Una persona del fichero PERSONAS.DAT se considerará aceptable como candidato si tiene diferente sexo y que haya nacido en el mes y año 
// (El programa debe ser capaz de trabajar con cualquier número de personas en el fichero PERSONAS.DAT).

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
using namespace std;

const char *NOMBRE_ARCHIVO_PERSONAS = "PERSONAS.bin";
const char *NOMBRE_ARCHIVO_ACEPTADOS = "ACEPTADOS.dat";

struct Persona {
    char nombre[30];
    char sexo[2];
    char fechadenacimiento[10];
    int edad;
};

void MostrarDatosArchivo(const char *NOMBRE_ARCHIVO_PERSONAS);
bool EncontrarAceptadosPorSexo(const char encontrar[]);
bool EncontrarAceptadosPorFechaNac(const char buscar[]);
void EncontrarAceptados(const char *NOMBRE_ARCHIVO_PERSONAS, const char *NOMBRE_ARCHIVO_ACEPTADOS);

int main() {
    MostrarDatosArchivo(NOMBRE_ARCHIVO_PERSONAS);
    EncontrarAceptadosPorSexo("M");
    EncontrarAceptadosPorFechaNac("DD/MM/YYYY");
    EncontrarAceptados(NOMBRE_ARCHIVO_PERSONAS, NOMBRE_ARCHIVO_ACEPTADOS);
    return 0;
}

void MostrarDatosArchivo(const char *NOMBRE_ARCHIVO_PERSONAS) {
    cout << "*************DATOS ACTUALES DEL ARCHIVO****************" << endl;
    ifstream archivo(NOMBRE_ARCHIVO_PERSONAS, ios::binary);
    if (!archivo) {
        cout << "Error al abrir el archivo." << endl;
        exit(1);
    }
    Persona persona;
    while (archivo.read((char*)&persona, sizeof(Persona))){
        cout << "Nombre: " << persona.nombre << endl;
        cout << "Edad: " << persona.edad << endl;
        cout << "Sexo: " << persona.sexo << endl;
        cout << "Fecha de Nacimiento: " << persona.fechadenacimiento << endl;
        cout << endl;
    }
    archivo.close();
}

bool EncontrarAceptadosPorSexo(const char encontrar[2]){
    ifstream archivolectura;
    archivolectura.open(NOMBRE_ARCHIVO_PERSONAS, ios::binary);
    if (!archivolectura) {
        cout << "Error al abrir al archivo" <<endl;
        exit(1);
    }
    Persona persona;
    while (archivolectura.read((char*)&persona, sizeof(Persona))) {
        if(strcmp(encontrar, persona.sexo)!=0){
            return true;
        }
    }
    archivolectura.close();
    return false;
}

bool EncontrarAceptadosPorFechaNac(const char buscar[10]){
    ifstream archivoLeer;
    archivoLeer.open(NOMBRE_ARCHIVO_PERSONAS, ios::binary);
    if(!archivoLeer) {
        cout << "Error al abrir al archivo" << endl;
        exit (1);
    }
    Persona persona;
    while (archivoLeer.read((char*)&persona, sizeof(Persona))) {
        string mesAnio = persona.fechadenacimiento;
        mesAnio = mesAnio.substr(3, 7);
        if (mesAnio == buscar) {
            return true;
        }
    }
    archivoLeer.close();
    return false;
}

void EncontrarAceptados(const char *NOMBRE_ARCHIVO_PERSONAS, const char *NOMBRE_ARCHIVO_ACEPTADOS) {
    ifstream archivoentrada(NOMBRE_ARCHIVO_PERSONAS, ios::binary);
    ofstream archivosalida(NOMBRE_ARCHIVO_ACEPTADOS, ios::binary);
    if (!archivoentrada || !archivosalida){
        cout << "No se pudo abrir uno o ambos archivos" << endl;
        exit(1);
    }
    Persona persona;
    while (archivoentrada.read((char*)&persona, sizeof(Persona))){
        if(EncontrarAceptadosPorSexo(persona.sexo) && EncontrarAceptadosPorFechaNac(persona.fechadenacimiento + 3)){
            cout <<"MODIFICACION DE DATOS PARA LAS PERSONAS ACEPTADAS: "<< endl;
            archivosalida.write((char*)&persona, sizeof(Persona));
            cout<<"\tNOMBRE: "<<persona.nombre<<endl;
            cout<<"\tSEXO: "<<persona.sexo<<endl;
            cout<<"\tFECHA DE NACIMIENTO: "<<persona.fechadenacimiento<<endl;
            cout<<"\tEDAD: "<<persona.edad<<endl;
        }
    }
    archivoentrada.close();
    archivosalida.close();
}

