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

