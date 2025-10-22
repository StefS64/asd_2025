#include <iostream>
#include <algorithm>

constexpr int MAX_N = 1001;
constexpr int MAX_M = 1001;
constexpr int MAX_K = 11;

constexpr int CUT_OFF = 1'000'000'000;

int dp[MAX_N][MAX_M][MAX_K];        // Keep the ways in how many one can get to square a, b while collecting 0 <= l < k  mushrooms. [k] denotes >= k mushrooms.
bool mush[MAX_N][MAX_M];            // Where is the mushrooms.

using namespace std;

void mushroom(int* states, int k) {
    if (k == 0) return; // when k==0 nothing to shift (we already count ">=0")
    states[k] = (states[k] + states[k-1]) % CUT_OFF;
    for (int i = k-1; i > 0; i--) {
        states[i] = states[i-1] % CUT_OFF;
    }
    states[0] = 0;
}

void update_states(int a, int b, int *new_val, int k) {
    for (int i = 0; i <= k; i++) {
        dp[a][b][i] += new_val[i];
        dp[a][b][i] %= CUT_OFF;
    }
}

void add_states(int a, int b, int *new_val, int k, bool mush) {
    if (mush) {
        mushroom(dp[a][b], k);
    }
    for (int i = 0; i <= k; i++) {
        new_val[i] += dp[a][b][i];
        new_val[i] %= CUT_OFF;
    }
}


void print_table(int n, int m, int k)
{
    for (int l = 0; l <= k; l++)
    {
        cout << "-----" << l << "------" << endl;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= m; j++)
            {
                cout << dp[i][j][l] << " ";
            }
            cout << endl;
        }
    }
    cout << "next iteraion " << endl << endl;
}
void print_add_state(int* state, int k) {
    for (int i = 0; i <= k; i++) {
        cout << state[i] << " ";
    }
    cout << endl <<"----states-----" <<endl;
}
void print_mush(int n, int m) {
    for (int i =1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << mush[i][j] << " ";
        }
        cout << endl;
    }
}
int main() {
    int n, m, k, g;

    cin >> n >> m >> k >> g;

    int a, b;

    for (int i = 0; i < g; i++) {
       cin >> a >> b;
       mush[a][b] = true;
    }
    // print_mush(n,m);

    dp[1][0][0] = 1;

    for (int j = 1; j <= m; j++) {
        int new_comb[11] = {};
        // cout <<"up" << '\n';
        for (int i = 1; i <= n; i++) {
            add_states(i, j - 1, new_comb, k, false);
            if (mush[i][j]) {
                // cout <<"mushroom: " << i <<" " << j <<endl;
                mushroom(new_comb, k);
            }
            update_states(i, j, new_comb, k);
            // print_add_state(new_comb, k);
        }
        
        std::fill(new_comb, new_comb + 11, 0);
 
        // cout << "down" << '\n';

        for (int i = n; i >= 1; i--) {
            bool is_mush = false;
            if (mush[i][j]) {
                mushroom(new_comb, k);
                is_mush = true;
            }
            // print_add_state(new_comb, k);
            update_states(i, j, new_comb, k); 
            add_states(i, j - 1, new_comb, k, is_mush);
        }
        // print_table(n, m, k);
    }

    cout << dp[n][m][k] << '\n';
}