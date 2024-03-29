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
// Github: https://github.com/Caceres-A01706972/TC2037/tree/main/Situación%20Problema/Resaltador%20de%20Sintaxis%202 
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
#include "funciones_regex.h"

const int HILOS = 8; //Threads to be used

using namespace std;


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
        // Para guardar palabras x
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
    vector<string> vectorPalabras;
    
    for(int i = 1; i < size; i++){ // todo el codigo de secuencial tiene que ir dentro de este loop. Para poder hacer el resaltador para cada archivo.
        string line;
        string codigo;
        ifstream inputFile(rutas[i]); //reads file

        if (inputFile.is_open()) {

            //while loop to read the file line by line 
            while(getline(inputFile, line)){
                codigo += line;
                codigo += "\n";
            }
            
            vectorPalabras = llenarVectorPalabras(codigo, vectorPalabras); 

            //Esto imprime ResaltadorSecuencial_#1.html
            string outFile_name = "Resaltador_Secuencial_#" + to_string(i) + ".html";

            ofstream htmlOutput(outFile_name);

            htmlOutput << "<!DOCTYPE html> \n";
            htmlOutput << "<html lang = 'es'> \n";
            htmlOutput << "<head> \n\t";
            htmlOutput << "<meta charset = 'UTF-8'> \n\t";
            htmlOutput << "<meta http - equiv = 'X-UA-Compatible' content = 'IE=edge'>\n\t";
            htmlOutput << "<meta name = 'viewport' content = 'width=device-width, initial-scale=1.0'>\n\t";
            htmlOutput << "<title> Secuencial "<<to_string(i)<<"</title> <link rel = 'stylesheet' href = 'styles.css'>";
            htmlOutput << "</head>\n<body>\n";

            for(int posPalabra = 0; posPalabra < vectorPalabras.size(); posPalabra++){
                string palabra = vectorPalabras[posPalabra];
                if(isInclude(palabra)){
                    regex lessThan("<");
                    regex greaterThan(">");
                    string word = regex_replace(palabra, lessThan, "&lt;");
                    word = regex_replace(word, greaterThan, "&gt;");
                    htmlOutput << "<span class='include'>" << word << "</span>";
                } else if(isFromLanguage(palabra)){
                    htmlOutput << "<span class='reserved'>" << palabra << "</span>";
                } else if(isNumero(palabra)){
                    htmlOutput << "<span class='numero'>" << palabra << "</span>";
                } else if(isVariable(palabra)){
                    htmlOutput << "<span class='variable'>" << palabra << "</span>";
                } else if(isOperador(palabra)){
                    regex lessThan("<");
                    regex greaterThan(">");
                    string word = regex_replace(palabra, lessThan, "&lt;");
                    word = regex_replace(word, greaterThan, "&gt;");
                    htmlOutput << "<span class='operador'>" << word << "</span>";
                } else if(isComment(palabra)){
                    htmlOutput << "<span class='comment'>" << palabra << "</span>";
                } else if(isCadena(palabra)){
                    htmlOutput << "<span class='string'>" << palabra << "</span>";
                } else if(isEspacio(palabra)){
                    htmlOutput << " ";
                } else if(isSalto(palabra)){
                    htmlOutput << "\n"; 
                    htmlOutput << "<br>";
                } else if(isTab(palabra)){
                    htmlOutput << "\t";
                    htmlOutput << "&emsp;";
                } else if(isEncierra(palabra)){
                    htmlOutput << "<span class='encierra'>" << palabra << "</span>";
                } else if(isPuntuacion(palabra)){
                    htmlOutput << "<span class='puntuacion'>" << palabra << "</span>";
                }
            }

            htmlOutput << "\n</body>\n</html>";
            htmlOutput.close();
            
        }
        inputFile.close();
        vectorPalabras.clear();
    }
}

//Estructura de Bloque
typedef struct {
    int start, end;
    string* arreglo;
} Block;

void* resaltadorConcurrente(void* params){
    vector<string> vectorPalabras;

    Block *block;
    block = (Block*) params;

    for(int i = block->start; i < block->end; i++){
        string line;
        string codigo;
        ifstream inputFile(block->arreglo[i]); //reads file

        if(inputFile.is_open()){
            while(getline(inputFile, line)){
                codigo += line;
                codigo += "\n";
            }

            vectorPalabras = llenarVectorPalabras(codigo, vectorPalabras); 

            //Esto imprime ResaltadorSecuencial_#1.html
            string outFile_name = "Resaltador_Concurrente_#" + to_string(i) + ".html";

            ofstream htmlOutput(outFile_name);

            htmlOutput << "<!DOCTYPE html> \n";
            htmlOutput << "<html lang = 'es'> \n";
            htmlOutput << "<head> \n\t";
            htmlOutput << "<meta charset = 'UTF-8'> \n\t";
            htmlOutput << "<meta http - equiv = 'X-UA-Compatible' content = 'IE=edge'>\n\t";
            htmlOutput << "<meta name = 'viewport' content = 'width=device-width, initial-scale=1.0'>\n\t";
            htmlOutput << "<title> Secuencial "<<to_string(i)<<"</title> <link rel = 'stylesheet' href = 'styles.css'>";
            htmlOutput << "</head>\n<body>\n";

            for(int posPalabra = 0; posPalabra < vectorPalabras.size(); posPalabra++){
                string palabra = vectorPalabras[posPalabra];
                if(isInclude(palabra)){
                    regex lessThan("<");
                    regex greaterThan(">");
                    string word = regex_replace(palabra, lessThan, "&lt;");
                    word = regex_replace(word, greaterThan, "&gt;");
                    htmlOutput << "<span class='include'>" << word << "</span>";
                } else if(isFromLanguage(palabra)){
                    htmlOutput << "<span class='reserved'>" << palabra << "</span>";
                } else if(isNumero(palabra)){
                    htmlOutput << "<span class='numero'>" << palabra << "</span>";
                } else if(isVariable(palabra)){
                    htmlOutput << "<span class='variable'>" << palabra << "</span>";
                } else if(isOperador(palabra)){
                    regex lessThan("<");
                    regex greaterThan(">");
                    string word = regex_replace(palabra, lessThan, "&lt;");
                    word = regex_replace(word, greaterThan, "&gt;");
                    htmlOutput << "<span class='operador'>" << word << "</span>";
                } else if(isComment(palabra)){
                    htmlOutput << "<span class='comment'>" << palabra << "</span>";
                } else if(isCadena(palabra)){
                    htmlOutput << "<span class='string'>" << palabra << "</span>";
                } else if(isEspacio(palabra)){
                    htmlOutput << " ";
                } else if(isSalto(palabra)){
                    htmlOutput << "\n"; 
                    htmlOutput << "<br>";
                } else if(isTab(palabra)){
                    htmlOutput << "\t";
                    htmlOutput << "&emsp;";
                } else if(isEncierra(palabra)){
                    htmlOutput << "<span class='encierra'>" << palabra << "</span>";
                } else if(isPuntuacion(palabra)){
                    htmlOutput << "<span class='puntuacion'>" << palabra << "</span>";
                }
            }

            htmlOutput << "\n</body>\n</html>";
            htmlOutput.close();
        }
    }
    pthread_exit(0);
}

int main(int argc, char** argv){
    double sequential, concurrent; // Tiempo en ms
    string *rutasArchivos;
    pthread_t hilos[HILOS];
    Block blocks[HILOS];
    int blockSize;

    const int arraySize = argc;

    rutasArchivos = new string[arraySize];

    for(int i = 1; i < arraySize; i++){
        rutasArchivos[i] = argv[i];
    }
    
//========================SEQUENTIAL========================================================
    cout << "\nEJECUTANDO DE MANERA SECUENCIAL: " << endl;
    sequential = 0;
    start_timer();
    resaltadorSec(rutasArchivos, arraySize);
    sequential += stop_timer();

    cout << "Sequential Time = " << setprecision(5) << sequential << " ms\n" << endl;
//==========================================================================================

//========================CONCURRENT========================================================
    blockSize = arraySize / HILOS;

    for(int i = 0; i < HILOS; i++){
        blocks[i].start = i * blockSize;
        blocks[i].end = (i != (HILOS - 1))? (i + 1) * blockSize : arraySize;
        blocks[i].arreglo = rutasArchivos;
    }

    cout << "EJECUTANDO DE MANERA CONCURRENTE: " << endl;
    concurrent = 0;
    start_timer();
    for(int i = 0; i < HILOS; i++){
        pthread_create(&hilos[i], NULL, resaltadorConcurrente, (void*)&blocks[i]);
    }

    for(int i = 0; i < HILOS; i++){
        pthread_join(hilos[i], NULL);
    }
    concurrent += stop_timer();
    cout << "Concurrent Time = " << setprecision(5) << concurrent << " ms\n" << endl;
//==========================================================================================

    cout << "SPEED UP = " << setprecision(5) << (sequential / concurrent) << " ms\n" << endl;

    delete [] rutasArchivos;
  
    return 0;
}
