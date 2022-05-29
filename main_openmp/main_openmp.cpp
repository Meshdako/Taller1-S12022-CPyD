// C++
#include <iostream>
#include <fstream>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <vector>
#include <cmath>

#include <omp.h>

using namespace std;

void Integrantes()
{
    cout << "Los integrantes son: \n\t1. Martín Sobarzo.\n\t2. Cristobal Abarca.\n\t3. Rodrigo Ubilla." << endl;
}

void Evaluar(ofstream *Archivo_Aux, vector<string> Aux)
{
    //cout << "Está en la función externa" << endl;

    char delimitador = ';';

    //int Threads = omp_get_thread_num();
    //cout << "Hilos disponibles: "<< Threads << endl;

    string Token[3];
    //vector<string> Datos;
    vector<string> PregCorrectas = {"\"A\"", "\"E\"", "\"C\"", "\"B\"", "\"B\"", "\"D\"", "\"A\"", "\"B\"", "\"E\"", "\"C\"", "\"B\"", "\"D\""};

#pragma omp parallel
{
    int RespCorrectas[3], RespIncorrectas[3], RespOmitidas[3];
    int ID = omp_get_thread_num();

    #pragma omp for
    for(int i = 0; i < Aux.size(); i++){
        stringstream columnas(Aux.at(i));
        
        getline(columnas, Token[ID], delimitador);

        #pragma omp orderd
        for(int j = 0; j < PregCorrectas.size(); j++){
            string Dato;
            getline(columnas, Dato, delimitador);
            
            if(Dato == "\"-\""){
                RespOmitidas[ID] += 1;
                //cout << "Hilo: " << omp_get_thread_num() << " = " << "Omitidas " << RespOmitidas << endl;
            }
            else{
                if(Dato == PregCorrectas.at(j)){
                    RespCorrectas[ID] += 1;
                    //cout << "Hilo: " << omp_get_thread_num() << " = " << "Correctas " << RespCorrectas << endl;
                }
                else{
                    RespIncorrectas[ID] += 1;
                    //cout << "Hilo: " << omp_get_thread_num() << " = " << "Incorrectas " << RespIncorrectas << endl;
                }
            }
        }
        
        float Puntaje, NotaFinal;

        #pragma omp critical
        {
            Puntaje = (RespCorrectas[ID] * 0.5) - (RespIncorrectas[ID] * 0.12);
            //cout << "Hilo: " << omp_get_thread_num() << " = " << "Puntaje " << Puntaje << endl;
            
            if(Puntaje < 0)
                Puntaje = 0;
            
            NotaFinal = 1 + Puntaje;
            //cout << "Hilo: " << omp_get_thread_num() << " = " << "Nota Final " << NotaFinal << endl;
            NotaFinal = round(NotaFinal * 10) / 10.0;
            
            
            //cout << "Hilo: " << omp_get_thread_num() <<  " = " << Token << "/" << RespCorrectas << "-" << RespIncorrectas << "-" << RespOmitidas << "-" << Puntaje << "-" << NotaFinal << endl;
            *Archivo_Aux << Token[ID] << ";" << "\"" << RespCorrectas[ID] << "\"" << ";" << "\"" << RespIncorrectas[ID] << "\"" << ";" << "\"" << RespOmitidas[ID] << "\"" << ";" << "\"" << Puntaje << "\"" << ";" << "\"" << NotaFinal << "\"" << endl;
        }   //end critical
    }   //end for()
    
    #pragma omp barrier
    RespCorrectas[ID] = RespIncorrectas[ID] = RespOmitidas[ID] = 0;
}   //end parallel
    Aux.clear();
}

void LeerEscribir()
{
    ifstream archivo_origen;  // Pruebas
    ofstream archivo_destino; // Resultados

    vector<string> filas;
    string linea;
    int cont = 0;

    // Abrimos el archivo que debemos leer.
    archivo_origen.open("pruebas.csv", ios::in);

    if (archivo_origen.fail())
    {
        cout << "Error: no se pudo abrir el archivo pruebas.csv" << endl;
        exit(1);
    }

    // Destino de los resultados obtenidos.
    archivo_destino.open("resultados_MP.csv", ios::out);

    if (archivo_destino.fail())
    {
        cout << "Error: no se puede abrir el archivo resultadospruebas.csv" << endl;
        exit(1);
    }

    stringstream Columnas;
    Columnas << "\"Identificador de Estudiante\"" << ";" << "\"Preguntas correctas\"" << ";" << "\"Preguntas incorrectas\"" << ";" << "\"Preguntas omitidas\"" << ";" << "\"Puntaje\"" << ";" << "\"Nota\"";
    string PrimeraFila = Columnas.str();
    archivo_destino << PrimeraFila << endl;

    // Quitamos la primera línea.
    getline(archivo_origen, linea);

    // Comenzamos a leer el archivo.
    while (!archivo_origen.eof())
    {
        if (cont == 3)
        {
            //cout << "Entró al if" << endl;
            Evaluar(&archivo_destino, filas);

            // Reiniciamos nuestro contador.
            cont = 0;
            filas.clear();
            //exit(1);
        }

        // Guardamos de a 3 líneas.
        getline(archivo_origen, linea);
        filas.push_back(linea);

        cont++;
    }
    // Cerramos los archivos al finalizar el bucle.
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