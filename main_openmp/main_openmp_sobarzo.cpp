/*
Integrantes:
    *   Martín Sobarzo
    *   Rodrigo Ubilla
    *   Cristobal Abarca
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

#include "datos.h"

#define MAX 17000000

using namespace std;

datos DatosPrueba[MAX];

void Escribir(string Filas[])
{
    ofstream destino;

    //Destino de los resultados obtenidos.
    destino.open("resultadospruebasomp.csv", ios::out);

    if(destino.fail()){
        cout << "Error: no se puede abrir el archivo resultadospruebas.csv" << endl;
        exit(1);
    }

    //Ingresamos la primera línea al archivo de destino.
    stringstream Columnas;
    Columnas << "\"Identificador de Estudiante\"" << ";" << "\"Preguntas correctas\"" << ";" << "\"Preguntas incorrectas\"" << ";" << "\"Preguntas omitidas\"" << ";" << "\"Puntaje\"" << ";" << "\"Nota\"";
    string PrimeraFila = Columnas.str();
    destino << PrimeraFila << endl;

    for(int i = 0; i < MAX; i++){
        destino << Filas[i] << endl; 
    }
    
    destino.close();
}

string Linea(string nombre, int RespCorrectas, int RespIncorrectas, int RespOmitidas, int Puntaje, int NotaFinal)
{
    string Aux_Correctas, Aux_Incorrectas, Aux_Omitidas, Aux_Puntaje, Aux_NFinal;

    Aux_Correctas = "\"" + to_string(RespCorrectas) + "\"";
    Aux_Incorrectas = "\"" + to_string(RespIncorrectas) + "\"";
    Aux_Omitidas = "\"" + to_string(RespOmitidas) + "\"";
    Aux_Puntaje = "\"" + to_string(Puntaje) + "\"";
    Aux_NFinal = "\"" + to_string(NotaFinal) + "\"";

    string LineaDocumento = nombre + ";" + Aux_Correctas + ";" + Aux_Incorrectas + ";" + Aux_Omitidas + ";" + Aux_Puntaje + ";" + Aux_NFinal;


    return LineaDocumento;
}

void CalculoNotas()
{
    string LineaDocumento[MAX];
    string PregCorrectas[12] = {"\"A\"", "\"E\"", "\"C\"", "\"B\"", "\"B\"", "\"D\"", "\"A\"", "\"B\"", "\"E\"", "\"C\"", "\"B\"", "\"D\""};

    int RespCorrectas, RespIncorrectas, RespOmitidas;
    RespCorrectas = RespIncorrectas = RespOmitidas = 0;

    #pragma omp parallel
    {
        //Calculamos el puntaje del estudiante.
        #pragma omp for
        for(int i = 0; i < MAX; i++){
            
            #pragma omp critical
            {
                string RE[12] = DatosPrueba[i].getResultados();
                
                #pragma omp for
                for(int j = 0; j < 12; j++){
                    
                    #pragma omp critical
                    {
                        if(RE[j] == "\"-\""){
                            RespOmitidas++;
                        }
                        else{
                            if(RE[j].compare(PregCorrectas[i - 1]) == 0){
                                RespCorrectas++;
                            }
                            else{
                                RespIncorrectas++;
                            }
                        }
                    }
                }
                float Puntaje = (RespCorrectas * 0.5) - (RespIncorrectas * 0.12);
                Puntaje = roundf(Puntaje * 10) / 10;

                float NotaFinal = 1 + Puntaje;
                NotaFinal = roundf(NotaFinal * 10) / 10;

                if(NotaFinal < 1)
                    NotaFinal = 1;
                
                LineaDocumento[i] = Linea(DatosPrueba[i].getToken(), RespCorrectas,RespIncorrectas,RespOmitidas,Puntaje,NotaFinal);
                                
                RespCorrectas = RespIncorrectas = RespOmitidas = 0;
            }
        }
    }
}

void LeerArchivo()
{
    ifstream archivo;
    string linea;
    char delimitador = ';';

    //Abrimos el archivo que debemos leer.
    archivo.open("Taller01/pruebas.csv", ios::in);

    if(archivo.fail()){
        cout << "Error: no se pudo abrir el archivo pruebas.csv" << endl;
        exit(1);
    }

    //Omitimos la primera línea.
    getline(archivo, linea);
    getline(archivo, linea);

    //Variable para capturar los datos del archivo.
    string TokenEstudiante;
    string Datos[12];

    //Contador de preguntas correctas, incorrectas y omitidas.
    

    int i = 0;
    while(getline(archivo, linea)){
        stringstream stream(linea);
        getline(stream, TokenEstudiante, delimitador);
        getline(stream, Datos[0], delimitador);
        getline(stream, Datos[1], delimitador);
        getline(stream, Datos[2], delimitador);
        getline(stream, Datos[3], delimitador);
        getline(stream, Datos[4], delimitador);
        getline(stream, Datos[5], delimitador);
        getline(stream, Datos[6], delimitador);
        getline(stream, Datos[7], delimitador);
        getline(stream, Datos[8], delimitador);
        getline(stream, Datos[9], delimitador);
        getline(stream, Datos[10], delimitador);
        getline(stream, Datos[11], delimitador);

        DatosPrueba[i].ingresardatos(TokenEstudiante, &Datos[12]);
        i++;
    }
    
    //Cerramos los archivos al finalizar el bucle.
    archivo.close();

    CalculoNotas();
}


int main()
{
    LeerArchivo();
    cout << "Grabación hecha con éxito" << endl;
    return EXIT_SUCCESS;
}