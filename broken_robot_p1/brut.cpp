#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const long long INF = 1e18;

int n, k;
vector<long long> beads;

long long solve(int idx, int consecutive, bool used_k) {
    if (idx == n) return 0;

    // Skip the current bead
    long long skip = solve(idx + 1, 0, used_k);

    // Take the current bead
    long long take = -INF;
    if (consecutive < k) {
        take = beads[idx] + solve(idx + 1, consecutive + 1, used_k);
    } else if (!used_k) {
        take = beads[idx] + solve(idx + 1, consecutive + 1, true);
    }

    return max(skip, take);
}

int main() {
    cin >> n >> k;
    beads.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> beads[i];
    }

    cout << solve(0, 0, false) << endl;
    return 0;
}