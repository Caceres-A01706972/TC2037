// =================================================================
//
// File: concurrente1.cpp
// Author: Ricardo Andres Caceres Villibord A01706972                                            -
// Description: Calcula la suma de todos los numeros enteros pares
// contenidos en un arreglo de numeros enteros.
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

using namespace std;

const int size = 10000; //1e6
const int THREADS = 8;

//================================SEQUENTIAL============================
void pares(int *arr, int size, int *auxArr){
    int suma = 0;
    for(int i = 0; i < size; i++){
        if (arr[i]%2 == 0){
            suma += arr[i];
            auxArr[0] = suma;
        }
    }
    
    
}
//=======================================================================

//========================CONCURRENTE====================================
// typedef struct{
//     int start, end, *array;
// } Block;

// void* task(void* param) {
//     Block *block;

//     block = (Block*) param;
    
    
//     pthread_exit(0);
// }


//=======================================================================

int main(int argc, char* argv[]){
    double sequential, concurrent;
    int *array, blockSize;
    int *auxArr;
    // pthread_t tids[THREADS];
    // Block blocks[THREADS];
    
    array = new int[size];
    auxArr = new int[1];
    random_array(array, size);
//===========================SEQUENTIAL===================================
    sequential = 0;
    for(int i=0; i < N; i++){
        start_timer();

        // ADD CODE HERE
        
        pares(array, size, auxArr);

        sequential += stop_timer();
    }
    cout<<"\n SEQUENTIAL  SUMA NUMEROS PARES = ";
    cout << setw(4) << auxArr[0];
       
    cout<< "\n";
    cout<<"sequential average time = "<<setprecision(5)<<(sequential/N)<<" ms"<<endl;
//============================================================================

//============================CONCURRENTE=====================================
    
//     blockSize = size / THREADS;
//     for (int i = 0; i < THREADS; i++){
//         blocks[i].start = i * blockSize;
//         blocks[i].end = (i != (THREADS -1))? (i + 1) * blockSize : size;
//         blocks[i].array = array;
//     }

//     concurrent = 0;
//     for (int j = 0; j < N; j++){
//         start_timer();
//         for (int i = 0; i < THREADS; i++) {
//             pthread_create(&tids[i], NULL, task, (void*) &blocks[i]);
//         }

//         for (int i = 0; i < THREADS; i++) {
//             pthread_join(tids[i], NULL);
//         }
//         concurrent += stop_timer();
//     }
//     cout<<"\n CONCURRENTE NUMEROS PARES = ";
//     for (int i=2; i< DISPLAY; i++){
//         if (array[i]) {
//             cout << setw(4) << i;
//         }
//     }
//     cout << "\n";
//     cout << "concurrent average time = " << setprecision(5) << (concurrent / N) << " ms" << endl;
 

// //============================================================================

//     cout << "speed up = " << setprecision(2) << (sequential / concurrent) << endl;
//     cout<< "\n";
//     delete [] array;

    return 0;
}