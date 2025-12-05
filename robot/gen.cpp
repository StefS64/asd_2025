// Simple test generator for rob / rob_square
// Usage: ./gen [n] [m] [seed]
// Defaults: n=100, m=1000, seed=time-based
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n = 7;
    long long m = 30;
    unsigned long long seed = chrono::high_resolution_clock::now().time_since_epoch().count();

    if (argc > 1) n = atoi(argv[1]);
    if (argc > 2) m = atoll(argv[2]);
    if (argc > 3) seed = strtoull(argv[3], nullptr, 10);

    if (n < 1) n = 1;
    if (n > 200000) n = 200000; // respect problem limits
    if (m < 1) m = 1;

    mt19937_64 rng(seed);
    uniform_int_distribution<long long> dist(1, m);

    cout << n << " " << m << "\n";
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << dist(rng);
    }
    cout << "\n";
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << dist(rng);
    }
    cout << "\n";

    return 0;
}