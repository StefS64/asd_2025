#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

constexpr long long INF = 1'000'000'000'00LL;

int main()
{
    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<char> is_trap(n + 1, false);
    int trap;
    for (int i = 0; i < m; i++)
    {
        cin >> trap;
        if (trap >= 0 && trap <= n) is_trap[trap] = true;
    }

    vector<long long> dp(n + 1, INF);
    dp[0] = 0; // start

    for (int i = 1; i <= n; i++)
    {
        if (is_trap[i]) continue; // can't stand on a trap

        long long best = INF;
        if (dp[i - 1] < INF) best = dp[i - 1] + 1;
        if (i >= 5 && dp[i - 5] < INF) best = min(best, dp[i - 5] + 10);
        if (i >= 10 && dp[i - 10] < INF) best = min(best, dp[i - 10] + 100);

        dp[i] = best;
    }

    if (dp[n] >= INF)
    {
        cout << -1 << '\n';
    }
    else
    {
        cout << dp[n] << '\n';
    }

    return 0;
}