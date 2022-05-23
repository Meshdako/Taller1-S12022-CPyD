#ifndef DATOS_H
#define DATOS_H

#include <iostream>

using namespace std;

class datos
{
    private:
        string token;
        string resultados[12];
    public:
        //Constructor
        datos();

        //Setters
        void setToken(string x){token = x;}
        void setResultados(string x[12]){resultados[12] = x[12];}

        //Getters
        string getToken(){return token;}
        string getResultados(){return resultados[12];}

        void ingresardatos(string a, string b[12]){
            token = a;
            for(int i = 0; i < 12; i++){
                resultados[i] = b[i];
            }
        }
};

#endif //DATOS_H