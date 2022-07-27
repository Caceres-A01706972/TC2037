// CPP program to illustrate

// Implementation of clear() function
#include <iostream>
#include <vector>
using namespace std;
  
int main() {
    vector<int> myvector;
    
    int numero = 5;
    float numero2 = 0.32;
  
    // Vector becomes 1, 2, 3, 4, 5
  
    for(int i = 0; i < numero; i++){
        numero2 += numero;
    }

    cout << numero2;
    // vector becomes empty
  
    // Printing the vector
    
    return 0;
}