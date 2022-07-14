//EJEMPLO DE CLASE
// ELEVAR NUMEROS DE UN ARREGLO A UNA POTENCIA

#include <iostream>
#include <iomanip>
#include <cstring>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"
const int size = 10000000;
const int THREADS = 8;

using namespace std;

//===========================SEQUENTIAL======================
double power(int x, int n){
    int acum = 1;
    for(int i = 1; i <= n; i++){
        acum *= x;
    }
    return acum;
}

void applyPower(int *array, int size, int n){
    for(int i = 0; i < size; i++){
        array[i] = power(array[i], n);
    }
}
//=============================================================


//==================CONCURRENT================================
typedef struct{
    int start, end, *array, n;
} Block;

void* task(void* param){
    Block *block;
    block = (Block*) param;

    for(int i= block->start; i < block->end; i++){
        block->array[i] = power(block->array[i], block->n);
    }
    pthread_exit(0);
}

//============================================================

int main(int argc, char* argv[]){
    int *array, sequential, concurrent, blockSize;
    pthread_t tids[THREADS];
    Block blocks[THREADS];

    array = new int[size];
    memset(array, 2, sizeof(int) * size);
    display_array("array = ", array);

    //=================================SEQUENTIAL======================================
    sequential = 0;
    for (int j = 0; j < N; j++){
        start_timer();

        memset(array, 2, sizeof(int) * size);
        applyPower(array,size, 4);

        sequential += stop_timer();
    }

    display_array("array = ", array);
    cout<<"average time = "<<fixed<<setprecision(2)<<(sequential / N)<<" ms\n";
    //===================================================================================

    //==============CONCURRENT=========================================================
    blockSize = size / THREADS;
    for(int i= 0; i < THREADS; i++){
        blocks[i].start = i * blockSize;
        blocks[i].end = (i != (THREADS - 1))? (i + 1) * blockSize : size;
        blocks[i].array = array;
        blocks[i].n = 4;
    }
    
    concurrent = 0;
    for (int j = 0; j < N; j++){
        start_timer();

        memset(array, 2, sizeof(int) * size);

        for (int i = 0; i < THREADS; i++){
            pthread_create(&tids[i], NULL, task, (void*) &blocks[i]);
        }

        for (int i=0; i < THREADS; i++){
            pthread_join(tids[i], NULL);
        }

        concurrent += stop_timer();
    }
    display_array("array = ", array);
    cout<<"average time = "<<fixed<<setprecision(2)<<(concurrent / N)<<" ms\n";
//==========================================================================================

    cout<<"speedup = "<<fixed<<setprecision(5)<<(sequential / concurrent) << endl;

    delete [] array;

    return 0;
}
