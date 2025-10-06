# Problem

## Solution
We will create a dp[i][2]
dp[0][0] = 0
dp[0][1] = 0
with the meanings:
In both the ith element was taken.
dp[i][1] - taken K 
dp[i][0] - K was not taken.

now as seen in the code we have the dp formula.

We do a quick trick with the last elment the desired value is in dp[n][0], dp[n][1].