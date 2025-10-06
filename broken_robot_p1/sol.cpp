#include <iostream>

using namespace std;

long long dp[100'002][2];

const long long INF = 1'000'000'000'000'000'007;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    long long element;
    long long sum = 0;

    dp[0][0] = 0;
    dp[0][1] = INF;


    for (int i = 1; i <= n+1; i++)
    {
        if (i < n + 1)
        {
            cin >> element;
            sum += element;
        }
        else
        {
            element = 0;
        }

        long long minimal_k_working = INF;
        long long minimal_k_broken = INF;

        for (int j = 1; j <= k; j++)
        {
            if (i >= j)
            {
                minimal_k_working = min(dp[i - j][0], minimal_k_working);
                minimal_k_broken = min(dp[i - j][1], minimal_k_broken);
            }
        }

        if (i > k)
        {
            minimal_k_broken = min(dp[i - k - 1][0], minimal_k_broken);
        }

        dp[i][0] = minimal_k_working + element;
        dp[i][1] = minimal_k_broken + element;
        // cout << dp[i][0] << " " << dp[i][1] << " " << i << endl;
    }
    

    cout << sum - min(dp[n+1][1], dp[n+1][0]) << '\n';
}