#include <iostream>
#include <algorithm>

using namespace std;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    long long beg[n];
    long long ending[3 * n];
    pair<int,int> lower_end[3 * n];
    pair<int,int> lower_beg[n];

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
        ending[i + n] = ending[i] + m;
        ending[i + 2 * n] = ending[i] + 2 * m;
    }

    // cout << "begin" << endl;
    // for (int i = 0; i < n; i++) {
    //     cout << i <<": " << beg[i] << endl;
    // }

    // cout <<"end:" << endl;
    // for (int i = 0; i < 3*n; i++) {
    //     cout << i <<": " << ending[i] << endl;
    // }

    int j = 0;
    for (int i = 0; i < n; i++) {
        while (j < 3 * n && ending[j] < beg[i]) {
            j++;
        }
        lower_beg[i] = j - i > 0 ? make_pair(j - i, i): make_pair(0, i);
    }

    
    int k = 0;
    for (int i = 0; i < 3 * n; i++) {
        while (k < n && beg[k] <= ending[i]) {
            k++;
        }
        lower_end[i] = k > 0 ? make_pair(i - k + 1, i) : make_pair(0, i);
        ending[i] *= -1;
    }

    sort(lower_beg, lower_beg + n);
    sort(lower_end, lower_end + 3*n);
    // cout << "begin" << endl;
    // for (int i = 0; i < n; i++) {
    //     cout << i <<": " << lower_beg[i].first <<" "<< lower_beg[i].second << endl;
    // }

    // cout <<"end:" << endl;
    // for (int i = 0; i < 3*n; i++) {
    //     cout << i <<": " << lower_end[i].first <<" "<< lower_end[i].second << endl;
    // }
    long long best = (1LL << 62);

    // Calculate first pass manually
    long long cost = 0;
    for (int i = 0; i < n; ++i) {
        cost += beg[i] + ending[i];
        if (cost >= best)
            break;
    }


    if (cost < best)
        best = cost;

    int end_it = 0;
    int beg_it = 0;

    // cout <<"cost: " << cost << endl;

    while(lower_end[end_it].first == 0) {
        end_it++;
    }
    
    for (int s = 1; s < 2 * n; ++s) {
        while((lower_beg[beg_it].first == s) && beg_it < n) {
            int index = lower_beg[beg_it].second;
            cost -= 2LL*beg[index];
            beg_it++;
        }
        cost -= ending[s-1];
        cost += ending[s+n-1];

        while((lower_end[end_it].first == s) && end_it < 3*n) {
            int index = lower_end[end_it].second;
            ending[index] *= -1;
            if(s <= index < s+n) {
                cost += 2LL*ending[index];
            }

            end_it++;
        }
        // cout <<"cost: " << cost << endl;
        if (cost < best)
            best = cost;
    }

    cout << best << '\n';

    return 0;
}