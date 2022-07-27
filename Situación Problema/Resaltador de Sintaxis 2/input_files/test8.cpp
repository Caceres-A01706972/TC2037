#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <pthread.h>
#include "utils.h"

const int SIZE = 1000000001; //1e9
const int THREADS = 8;

using namespace std;

// =========================== SEQUENTIAL ==========================
void calculateUglyNumbers(int *array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = ( (i % 2 == 0) || (i % 3 == 0) || (i % 5 == 0) );
    }
}
// =================================================================

// =========================== CONCURRENT ==========================
typedef struct {
    int start, end, *array;
} Block;

void* task(void* param) {
    Block *block;

    block = (Block*) param;
    for (int i = block->start; i < block->end; i++) {
        block->array[i] = ( (i % 2 == 0) || (i % 3 == 0) || (i % 5 == 0) );
    }
    pthread_exit(0);
}
// =================================================================

int main(int argc, char* argv[]) {
	double sequential, concurrent;
    int *array, blockSize;
    pthread_t tids[THREADS];
    Block blocks[THREADS];
	
    array = new int[SIZE];

    // =========================== SEQUENTIAL ==========================
    sequential = 0;
    for (int i = 0; i < N; i++) {
		start_timer();

		calculateUglyNumbers(array, (SIZE + 1));

		sequential += stop_timer();
	}

    cout << "ugly numbers =";
    for (int i = 1; i < DISPLAY; i++) {
        if (array[i]) {
            cout << setw(4) << i;
        }
    }
    cout << "\n";
    cout << "sequential average time = " << setprecision(5) << (sequential / N) << " ms" << endl;
    // =================================================================
    // =========================== CONCURRENT ==========================
    blockSize = SIZE / THREADS;
    for (int i = 0; i < THREADS; i++) {
        blocks[i].start = i * blockSize;
        blocks[i].end = (i != (THREADS - 1))? (i + 1) * blockSize : SIZE;
        blocks[i].array = array;
    }

    concurrent = 0;
    for (int j = 0; j < N; j++) {
        start_timer();
        for (int i = 0; i < THREADS; i++) {
            pthread_create(&tids[i], NULL, task, (void*) &blocks[i]);
        }

        for (int i = 0; i < THREADS; i++) {
            pthread_join(tids[i], NULL);
        }
        concurrent += stop_timer();
    }
    cout << "ugly numbers =";
    for (int i = 1; i < DISPLAY; i++) {
        if (array[i]) {
            cout << setw(4) << i;
        }
    }
    cout << "\n";
    cout << "concurrent average time = " << setprecision(5) << (concurrent / N) << " ms" << endl;
    // =================================================================

    cout << "speed up = " << setprecision(2) << (sequential / concurrent) << endl;
    delete [] array;

    return 0;
}