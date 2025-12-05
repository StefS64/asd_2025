#include <iostream>
#include <algorithm>

using namespace std;
int main() {
        ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int beg[n];
    int ending[3*n];
    
    for (int i = 0; i < n; i++) {
        cin >> beg[i];
        beg[i] += m;
    }

    for (int i = 0; i < n; i++) {
        cin >> ending[i];
    }
 
    sort(ending, ending + n);
    sort(beg, beg + n);

    for (int i = 0; i < n; i++) {
        ending[i+n] = ending[i] + m;
        ending[i+2*n] = ending[i] + 2*m;
    }

    
    // We'll do an O(n^2) sliding-window brute force.

    long long best = (1LL<<62);

    for (int s = 0; s < 2*n; ++s) {
        long long cost = 0;
        for (int i = 0; i < n; ++i) {
            int dist = abs(ending[s+i] - beg[i]);
            cost += dist;
            if (cost >= best) break;
        }
        if (cost < best) best = cost;
    }

    cout << best << '\n';

    return 0;
}