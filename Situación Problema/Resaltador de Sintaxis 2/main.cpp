// =================================================================
//
// ACTIVIDAD INTEGRADORA 5.3 RESALTADOR DE SINTAXIS PARALELO
// Author: Ricardo Andres Caceres Villibord A01706972
// Description: Resaltador de Sintaxis de C++ utilizando MULTIHILOS
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// Github:
// =================================================================

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <string>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <regex>
#include <fstream>
#include "utils.h"

const int HILOS = 8; //Threads to be used

using namespace std;



bool isdelimitador (char letra) {
    char delimitadores[] = { '(', ')', '[', ']', '{', '}', '<', '>', ',', ';', '+', '-', '*', '%', '/', '\n', ' ', '\t' };
    for(int i = 0; i < 18; i++){
        if(letra == delimitadores[i]){
            return true;
        } 
    }
    return false;
    
}

vector<string> llenarVectorPalabras(string codigo, vector<string> vectorPalabras){
    string palabra = "";

    //Ciclo para ir guardando cada palabra como un string dentro del vectorPalabras.
    for(int i = 0; i < codigo.length(); i++){

        //Para capturar un #include <LIBRERIA> como una sola palabra
        //Entonces asi vectorPalabras[0] tendria a #include <LIBRERIA>
        if(codigo[i] == '#'){
            for(int posLetra = i; posLetra < codigo.length(); posLetra++){
                if(codigo[posLetra + 1] == '>'){
                    palabra += codigo[posLetra];
                    palabra += codigo[posLetra + 1];
                    vectorPalabras.push_back(palabra);
                    palabra = "";
                    i = posLetra + 2;
                    break;
                } else{
                    palabra += codigo[posLetra];
                }
            }
        }

        //Para capturar un comentario //Comentario Comentario en una sola palabra
        if(codigo[i] == '/' && codigo[i+1] == '/'){
            for(int posLetra = i; posLetra < codigo.length(); posLetra++){
                if(codigo[posLetra + 1] == '\n'){
                    palabra += codigo[posLetra];
                    vectorPalabras.push_back(palabra);
                    palabra = "";
                    i = posLetra + 2;
                    break;
                } else{
                    palabra += codigo[posLetra];
                }
            }
        } 

        if(isdelimitador(codigo[i])){
            palabra = codigo[i];
            vectorPalabras.push_back(palabra);
            palabra = "";
        }

        //Para capturar un string "EJEMPLO DE STRING" en una sola palabra
        if(codigo[i] == '"'){
            for(int posLetra = i; posLetra < codigo.length(); posLetra++){
                if(codigo[posLetra + 1] == '"'){
                    palabra += codigo[posLetra];
                    palabra += codigo[posLetra + 1];
                    vectorPalabras.push_back(palabra);
                    palabra = "";
                    i = posLetra + 1;
                    break;
                } else{
                    palabra += codigo[posLetra];
                }
                
            }
            
        }

        //Si el siguiente no es delimitador, lo guarda en la variable palabra.
        // Para 
        else if(!isdelimitador(codigo[i])){
            palabra += codigo[i];
            if(isdelimitador(codigo[i + 1])){
                vectorPalabras.push_back(palabra);
            }
        }   
    }
    return vectorPalabras;
}

void resaltadorSec(string *rutas, int size){
    for(int i = 1; i < size; i++){
        cout<<i<<": "<<rutas[i]<<endl;
    }

    vector<string> vectorPalabras;
    string line;
    string codigo;
    ifstream inputFile(rutas[1]); //reads file
    
    //while loop to read the file line by line 
    while(getline(inputFile, line)){
        // cout<<line<<endl;
        codigo += line;
        codigo += "\n";
    }
    cout<<codigo<<endl;

    vectorPalabras = llenarVectorPalabras(codigo, vectorPalabras); 
    // cout<<vectorPalabras[0]<<endl;
    // cout<<vectorPalabras[1]<<endl;
    // cout<<vectorPalabras[2]<<endl;
    for(int i = 0; i < vectorPalabras.size(); i++){
        cout<<vectorPalabras[i]<<endl;
    }
    
}

int main(int argc, char** argv){

    double sequential, concurrent; // Tiempo en ms
    string *rutasArchivos;

    const int arraySize = argc;

    rutasArchivos = new string[arraySize];

    for(int i = 1; i < arraySize; i++){
        rutasArchivos[i] = argv[i];
    }
    
    // for(int i = 0; i < arraySize; i++){
    //     cout<<rutasArchivos[i]<<endl;
    // }

//========================SEQUENTIAL========================================================
    cout << "SECUENCIAL: \n" << endl;
    sequential = 0;
    start_timer();
    resaltadorSec(rutasArchivos, arraySize);
    sequential += stop_timer();

    cout << "Sequential Time = " << setprecision(5) << sequential << " ms" << endl;
//==========================================================================================


    cout << "You have entered " << argc
         << " arguments:" << "\n";
  
    for (int i = 0; i < argc; ++i)
        cout << "FILE #" << i << ": " << argv[i] << "\n";
  
    return 0;
}
