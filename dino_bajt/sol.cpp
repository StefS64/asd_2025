#include <iostream>

using namespace std;

constexpr long long INF = 1'000'000'000'00;
int main()
{
    int n, m;
    cin >> n >> m;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long dp[(m + 1) * 20 + 1];
    long long ans = 0;
    int trap = 0;
    int last_trap = 0;
    int last_trap_rel = 0;

    for (int i = 0; i <= m; i++)
    {
        if (i != m) {
            cin >> trap;
        } else {
            trap = n + 1;
        }

        if (trap - last_trap_rel > 20) {
            ans += trap - last_trap_rel - 20;
            last_trap_rel = trap;
            last_trap = last_trap + 20;
        } else {

            last_trap = last_trap + trap - last_trap_rel;
            last_trap_rel = trap;
        }

        dp[last_trap] = INF;

        // cout << last_trap << " rel:" << last_trap_rel << "ans :"<< ans << endl ;
    }

    // cout << endl <<  "traps" <<  endl;

    dp[0] = 0;

    for (int i = 1; i < last_trap; i++)
    {
        if (dp[i] != INF)
        {
            dp[i] = min(dp[i - 1] + 1, min((i - 5) >= 0 ? dp[i - 5] + 10 : INF, (i - 10 )>= 0 ? dp[i - 10] + 100 : INF));
        }
        // cout << dp[i] << endl;
    }
    
    if (dp[last_trap - 1] >= INF)
    {
        cout << -1 << '\n';
    }
    else
    {
        cout << dp[last_trap - 1] + ans << '\n';
    }
}