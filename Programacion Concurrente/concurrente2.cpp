// =================================================================
//
// File: exercise2.cpp
// Author: Ricardo Andres Caceres Villibord A01706972
// Description: calcula la suma de to dos los números enteros
// pares contenidos en un arreglo de números enteros
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

const int size = 1000000; //1e6
const int THREADS = 8;

using namespace std;

// =========================== SEQUENTIAL ==========================
int sumaPares(int *arr, int size){
    int suma = 0;
    for(int i = 0; i < size; i++){
        if (arr[i]%2 == 0){
            suma += arr[i];
        }
    }
    return suma;   
}
// =================================================================

// =========================== CONCURRENT ==========================
typedef struct{
    int start, end, *array, localResult;
} Block;

void* task(void* param){
    Block *block;
    int suma;

    block = (Block*) param;
    suma = 0;
    for(int i = block->start; i < block->end; i++){
        if(block->array[i]%2 == 0){
            suma += block->array[i];
        }
    }
    block->localResult = suma;
    pthread_exit(0);
}

// =================================================================

int main(int argc, char* argv[]) {
	double sequential, concurrent, blockSize;
    int *array, result;
    pthread_t tids[THREADS];
    Block blocks[THREADS];
	
    array = new int[size];
    random_array(array, size);
    display_array("array: ", array);

    // =========================== SEQUENTIAL ==========================
    sequential = 0;
    for (int i = 0; i < N; i++) {
		start_timer();

        result = sumaPares(array, size);
        
        sequential += stop_timer();
	}
    cout << "\nresult = " << fixed << setprecision(0) << result <<endl;
    cout << "sequential average time = " << setprecision(5) << (sequential / N) << " ms" << endl;
    // =================================================================

    // =========================== CONCURRENT ==========================
    blockSize = size / THREADS;
    for(int i = 0; i < THREADS; i++){
        blocks[i].start = i * blockSize;
        blocks[i].end = (i != (THREADS - 1))? (i + 1) * blockSize : size;
        blocks[i].array = array;
        blocks[i].localResult = result;
    }

    concurrent = 0;
    for(int j =0; j < N; j++){
        start_timer();
        for(int i = 0; i < THREADS; i++){
            pthread_create(&tids[i], NULL, task, (void*) &blocks[i]);
        }
        result = 0;
        for(int i = 0; i <THREADS; i++){
            pthread_join(tids[i], NULL);
            result += blocks[i].localResult;
        }
        concurrent += stop_timer();
    }

    cout << "result = " << fixed << setprecision(0) << result << endl;
    cout << "concurrent average time = " << setprecision(5) << (concurrent / N) << " ms" << endl;
    // =================================================================
    cout << "speed up = " << setprecision(5) << (sequential / concurrent) << " ms" << endl;
    
    delete [] array;

    return 0;
}