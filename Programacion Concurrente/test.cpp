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
void primos(int *arr, int size){
    for (int i = 2; i < size; i++){// i starts at 2 because the numbers 1 and 2 are by default prime numbers.
            int x = 0;//a variable to check if a number is prime. If it gets set to 1 the number is not prime.
        for (int j = 2; j < i; j++){//this loop divides the number by 2 up to itself and if the remainder is 0 sets x = 1.
            if (i%j == 0){
                x = 1;
                arr[i] = 0;
                break;
            }
        }
        if (x == 0){//if the x = 1 flag is never set the number is prime.
            arr[i]= i;
        }
    } 
}
//=======================================================================

//========================CONCURRENTE====================================
typedef struct{
    int start, end, *array;
} Block;

void* task(void* param) {
    Block *block;

    block = (Block*) param;
    for(int i = block->start; i < block->end; i++){
        int x = 0; //to check if its prime. If it gets set to 1 the number is not prime.
        for (int j = 2; j < i; j++){
            if (i%j == 0){
                x = 1;
                block->array[i] = 0;
                break;
            }
        }
        if (x == 0){
            block->array[i] = i;
        }
    }
    
    pthread_exit(0);
}


//=======================================================================

int main(int argc, char* argv[]){
    double sequential, concurrent;
    int *array, blockSize;
    pthread_t tids[THREADS];
    Block blocks[THREADS];
    
    array = new int[size];

//===========================SEQUENTIAL===================================
    sequential = 0;
    for(int i=0; i < N; i++){
        start_timer();
    
        // ADD CODE HERE
        primos(array, size);

        sequential += stop_timer();
    }
    cout<<"\n SEQUENTIAL PRIMOS = ";
    for (int i = 2; i < DISPLAY; i++) {
        if (array[i]) {
            cout << setw(4) << i;
        }
    }
    cout<< "\n";
    cout<<"sequential average time = "<<setprecision(5)<<(sequential/N)<<" ms"<<endl;
//============================================================================

//============================CONCURRENTE=====================================
    
    blockSize = size / THREADS;
    for (int i = 0; i < THREADS; i++){
        blocks[i].start = i * blockSize;
        blocks[i].end = (i != (THREADS -1))? (i + 1) * blockSize : size;
        blocks[i].array = array;
    }

    concurrent = 0;
    for (int j = 0; j < N; j++){
        start_timer();
        for (int i = 0; i < THREADS; i++) {
            pthread_create(&tids[i], NULL, task, (void*) &blocks[i]);
        }

        for (int i = 0; i < THREADS; i++) {
            pthread_join(tids[i], NULL);
        }
        concurrent += stop_timer();
    }
    cout<<"\n CONCURRENTE Primos = ";
    for (int i=2; i< DISPLAY; i++){
        if (array[i]) {
            cout << setw(4) << i;
        }
    }
    cout << "\n";
    cout << "concurrent average time = " << setprecision(5) << (concurrent / N) << " ms" << endl;
 

//============================================================================

    cout << "speed up = " << setprecision(2) << (sequential / concurrent) << endl;
    cout<< "\n";
    delete [] array;

    return 0;
}