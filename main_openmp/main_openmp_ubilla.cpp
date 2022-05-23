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
using namespace std;

void LeerEscribir()
{
    ifstream archivo;
    string linea;
    char delimitador = ';';
    int cont=0;
    ofstream destino;

    //Destino de los resultados obtenidos.
    destino.open("resultadospruebas.csv", ios::out);

    if(destino.fail()){
        cout << "Error: no se puede abrir el archivo resultadospruebas.csv" << endl;
        exit(1);
    }
    
    //Abrimos el archivo que debemos leer.
    archivo.open("pruebas.csv", ios::in);

    if(archivo.fail()){
        cout << "Error: no se pudo abrir el archivo pruebas.csv" << endl;
        exit(1);
    }
    while (getline(archivo,linea))
    {
        cont++;
    }
    
    archivo.close();

    //Abrimos el archivo que debemos leer.
    archivo.open("pruebas.csv", ios::in);

    if(archivo.fail()){
        cout << "Error: no se pudo abrir el archivo pruebas.csv" << endl;
        exit(1);
    }

    //Omitimos la primera línea.
    getline(archivo, linea);
    getline(archivo, linea);
    
    //Ingresamos la primera línea al archivo de destino.
    stringstream Columnas;
    Columnas << "\"Identificador de Estudiante\"" << ";" << "\"Preguntas correctas\"" << ";" << "\"Preguntas incorrectas\"" << ";" << "\"Preguntas omitidas\"" << ";" << "\"Puntaje\"" << ";" << "\"Nota\"";
    string PrimeraFila = Columnas.str();
    destino << PrimeraFila << endl;

    //Variable para capturar los datos del archivo.
    string Datos[13];
    string PregCorrectas[12] = {"\"A\"", "\"E\"", "\"C\"", "\"B\"", "\"B\"", "\"D\"", "\"A\"", "\"B\"", "\"E\"", "\"C\"", "\"B\"", "\"D\""};


    #pragma omp parallel{
            //Contador de preguntas correctas, incorrectas y omitidas.
            int threads=omp_get_num_threads();
            string Id[threads];
            int RespCorrectas[threads];
            int RespIncorrectas[threads];
            int RespOmitidas[threads];
            int Puntaje[threads];
            int NotaFinal[threads];
            for (size_t i = 0; i < threads; i++)
            {
                Id[i]="";
                RespCorrectas[i]=0;
                RespIncorrectas[i]=0;
                RespOmitidas[i]=0;
                Puntaje[i]=0;
                NotaFinal[i]=0;
            }
    }
    
    #pragma omp for 
    for(int i = 0; i < cont-2; i++){
        getline(archivo,linea);
        stringstream stream(linea);
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
        getline(stream, Datos[12], delimitador);
        
        Id[omp_get_thread_num()]=Datos[0];
        //Calculamos el puntaje del estudiante.
        for(int i = 1, j = 0; i < 13; i++, j++){
            if(Datos[i] == "\"-\""){
                RespOmitidas[omp_get_thread_num()]++;
            }
            else{
                if(Datos[i].compare(PregCorrectas[j]) == 0){
                    RespCorrectas[omp_get_thread_num()]++;
                }
                else{
                    RespIncorrectas[omp_get_thread_num()]++;
                }
            }
        }

        Puntaje[omp_get_thread_num()] = (RespCorrectas[omp_get_thread_num()] * 0.5) - (RespIncorrectas[omp_get_thread_num()] * 0.12);

        NotaFinal[omp_get_thread_num()] = 1 + Puntaje[omp_get_thread_num()];

        if(NotaFinal[omp_get_thread_num()] < 1)
            NotaFinal[omp_get_thread_num()] = 1;

        string Aux_Correctas, Aux_Incorrectas, Aux_Omitidas, Aux_Puntaje, Aux_NFinal;

        Aux_Correctas = "\"" + to_string(RespCorrectas[omp_get_thread_num()]) + "\"";
        Aux_Incorrectas = "\"" + to_string(RespIncorrectas[omp_get_thread_num()]) + "\"";
        Aux_Omitidas = "\"" + to_string(RespOmitidas[omp_get_thread_num()]) + "\"";
        Aux_Puntaje = "\"" + to_string(Puntaje[omp_get_thread_num()]) + "\"";
        Aux_NFinal = "\"" + to_string(NotaFinal[omp_get_thread_num()]) + "\"";

        string LineaDocumento = Datos[0] + ";" + Aux_Correctas + ";" + Aux_Incorrectas + ";" + Aux_Omitidas + ";" + Aux_Puntaje + ";" + Aux_NFinal;


        destino << LineaDocumento << endl; 

        RespCorrectas[omp_get_thread_num()] = RespIncorrectas[omp_get_thread_num()] = RespOmitidas[omp_get_thread_num()] = 0;
    }
    
    //Cerramos los archivos al finalizar el bucle.
    archivo.close();
    destino.close();
}

int main()
{
    LeerEscribir();
    cout << "Grabación hecha con éxito" << endl;
    return EXIT_SUCCESS;
}