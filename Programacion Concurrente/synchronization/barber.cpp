// =================================================================
//
// File: barber.cpp
// Author: Ricardo Andres Caceres Villibord A01706972
// Description: This file implements the Barbershop Problem
//              synchronization problem using pthreads.
//              To compile: g++ barber.cpp -lpthread
//
// Problem Source: https://greenteapress.com/semaphores/LittleBookOfSemaphores.pdf
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
//
// =================================================================

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <pthread.h>
#include <cstdlib>
#include <ctime>
#include <sys/time.h>

using namespace std;

const int MAX_CHAIRS = 3;
const int CUSTOMERSIZE = 6;
const int MAX_TIMES_CUSTOMER_TIRES = 5;

int customers = 0;
pthread_mutex_t mutex;
pthread_mutex_t customer;
pthread_mutex_t barber;
pthread_mutex_t customerDone;
pthread_mutex_t barberDone;

void* customerTh(void* param){
    int id;
    bool cuttingChairAvailable;

    id = *((int*) param);

    cout<<"Customer "<<id<<" is aproaching Barbershop.\n";
    for(int i = 0; i < MAX_TIMES_CUSTOMER_TIRES; i++){
        cuttingChairAvailable = true;
        pthread_mutex_lock(&mutex);
        if(customers == MAX_CHAIRS){
            cout<<"Customer"<<id<<": Its Full! I will come back later.\n";
            cuttingChairAvailable = false;
        } else{
            customers++;
        }
        pthread_mutex_unlock(&mutex);
        if(cuttingChairAvailable){
            pthread_mutex_unlock(&customer);
            pthread_mutex_lock(&barber);
            cout<<"Customer"<<id<<": Finally, my hair is being cut!\n";
            pthread_mutex_unlock(&customerDone);
            pthread_mutex_lock(&barberDone);
            pthread_mutex_lock(&mutex);
            customers--;
            pthread_mutex_unlock(&mutex);
            
        }
    }
    cout<<"Customer"<<id<<" has finished and leaves the store.\n";
    pthread_exit(0);
}

void* barberTH(void* param){
    while(1){
        cout<<"Barber waiting for a customer...\n";
        pthread_mutex_lock(&customer);
        cout<<"Barber: A customer arrived, I will cut your hair!\n";
        pthread_mutex_unlock(&barber);
        pthread_mutex_lock(&customerDone);
        pthread_mutex_unlock(&barberDone);
        cout<<"Barber: I finished your haircut! Bye!\n";
    }
    pthread_exit(0);
}


int main(int argc, char* argv[]) {
    pthread_t clientes[CUSTOMERSIZE];
    pthread_t barbero;
    int ids[CUSTOMERSIZE];
    pthread_mutex_init(&mutex, NULL);
    pthread_mutex_init(&customer, NULL);
    pthread_mutex_init(&barber, NULL);
    pthread_mutex_init(&customerDone, NULL);
    pthread_mutex_init(&barberDone, NULL);

    pthread_mutex_lock(&customer);
    pthread_mutex_lock(&barber);
    pthread_mutex_lock(&customerDone);
    pthread_mutex_lock(&barberDone);

    customers = 0;

    for(int i = 0; i < CUSTOMERSIZE; i++){
        ids[i] = i +1;
        pthread_create(&clientes[i], NULL, customerTh, &ids[i]);
    }
   
    pthread_create(&barbero, NULL, barberTH, NULL);

    for (int i = 0; i < CUSTOMERSIZE; i++) {
        pthread_join(clientes[i], NULL);
    }
    
    return 0;
}
