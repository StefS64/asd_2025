#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char* argv[]) {
    unsigned int seed = time(0); 
    if (argc > 1) {
        // seed = atoi(argv[1]); 
    }
    srand(seed);

    int n = rand() % 10 + 1; 
    int k = rand() % 3 + 1; 

    cout << n << " " << k << endl;

    for (int i = 0; i < n; i++) {
        cout << (rand() % 1001 - 1000) << " "; 
    }
    cout << endl;

    // cerr << "Seed: " << seed << endl; 

    return 0;
}