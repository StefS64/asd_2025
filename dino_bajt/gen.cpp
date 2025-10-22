#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int select(int a, int b) {
    if (b < a) return a; // defensive
    return a + rand() % (b - a + 1);
}

int main(int argc, char* argv[]) {
    unsigned int seed = time(0); 
    if (argc > 1) {
        seed = atoi(argv[1]); 
    }
    srand(seed);

    int n = rand() % 1000000 + 1; 
    int m = select(1, min(500, n)); // number of traps, between 0 and n

    cout << n << " " << m << endl;
    int last = 0;
    for (int i = 0; i < m; i++) {
        // choose next value in [last+1 .. n - (m-i-1)] so remaining slots fit
        int low = last + 1;
        int high = n - (m - i - 1);
        last = select(low, high);
        cout << last << " ";
    }
    cout << endl;

    return 0;
}