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
#include <cmath>

using namespace std;

void Integrantes()
{
    cout << "Los integrantes son: \n\t1. Martín Sobarzo.\n\t2. Cristobal Abarca.\n\t3. Rodrigo Ubilla." << endl;
}

void LeerEscribir()
{
    ifstream archivo_origen;
    ofstream archivo_destino;
    string linea;
    char delimitador = ';';
    
    //Abrimos el archivo que debemos leer.
    archivo_origen.open("pruebas.csv", ios::in);

    if(archivo_origen.fail()){
        cout << "Error: no se pudo abrir el archivo pruebas.csv" << endl;
        exit(1);
    }

    //Abrimos el archivo donde dejaremos los resultados obtenidos.
    archivo_destino.open("resultadospruebas.csv", ios::out);

    if(archivo_destino.fail()){
        cout << "Error: no se puede abrir el archivo resultadospruebas.csv" << endl;
        exit(1);
    }
    
    //Omitimos la primera línea.
    getline(archivo_origen, linea);
    
    //Ingresamos la primera línea al archivo de destino.
    stringstream Columnas;
    Columnas << "\"Identificador de Estudiante\"" << ";" << "\"Preguntas correctas\"" << ";" << "\"Preguntas incorrectas\"" << ";" << "\"Preguntas omitidas\"" << ";" << "\"Puntaje\"" << ";" << "\"Nota\"";
    string PrimeraFila = Columnas.str();
    archivo_destino << PrimeraFila << endl;

    //Variable para capturar los datos del archivo.
    string Datos[13];
    string PregCorrectas[12] = {"\"A\"", "\"E\"", "\"C\"", "\"B\"", "\"B\"", "\"D\"", "\"A\"", "\"B\"", "\"E\"", "\"C\"", "\"B\"", "\"D\""};

    //Contador de preguntas correctas, incorrectas y omitidas.
    int RespCorrectas, RespIncorrectas, RespOmitidas;
    RespCorrectas = RespIncorrectas = RespOmitidas = 0;

    while(getline(archivo_origen, linea)){
        stringstream stream(linea);
        getline(stream, Datos[0], delimitador);

        for(int i = 1; i < 13; i++){
            getline(stream, Datos[i], delimitador);
            if(Datos[i] == "\"-\""){
                RespOmitidas++;
            }
            else{
                if(Datos[i].compare(PregCorrectas[i - 1]) == 0){
                    RespCorrectas++;
                }
                else{
                    RespIncorrectas++;
                }
            }
        }
        
        float Puntaje, NotaFinal;
        Puntaje = (RespCorrectas * 0.5) - (RespIncorrectas * 0.12);
        Puntaje = round(Puntaje * 10) / 10.0;

        NotaFinal = 1 + Puntaje;
        NotaFinal = round(NotaFinal * 10) / 10.0;

        if(NotaFinal < 1)
            NotaFinal = 1;

        archivo_destino << Datos[0] << ";" << "\"" << RespCorrectas << "\"" << ";" << "\"" << RespIncorrectas << "\"" << ";" << "\"" << RespOmitidas << "\"" << ";" << "\"" << Puntaje << "\"" << ";" << "\"" << NotaFinal << "\"" << endl;

        RespCorrectas = RespIncorrectas = RespOmitidas = 0;
    }

    //Cerramos los archivos al finalizar el bucle.
    archivo_origen.close();
    archivo_destino.close();
}

int main()
{
    Integrantes();
    LeerEscribir();
    cout << "Grabación hecha con éxito" << endl;
    
    return EXIT_SUCCESS;
}