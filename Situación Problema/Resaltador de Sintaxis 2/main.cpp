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
#include "utils.h"

const int HILOS = 8; //Threads to be used

using namespace std;

int main(int argc, char** argv)
{
    cout << "You have entered " << argc
         << " arguments:" << "\n";
  
    for (int i = 0; i < argc; ++i)
        cout << "FILE #" << i << ": " << argv[i] << "\n";
  
    return 0;
}
