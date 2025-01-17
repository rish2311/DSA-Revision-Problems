// https://leetcode.com/problems/coin-change

// Solution 1 - Recursion TLE - indices 0 to n

class Solution {
public:
    int helper(vector<int>& coins, int amount, int ind) {
        if(amount == 0) return 0;
        if(amount < 0 || ind >= coins.size()) return INT_MAX-1;

        int res = -1;

        //exc
        res = helper(coins, amount, ind+1);

        //inc
        if(coins[ind] <= amount) {
            res = min(res, 1 + helper(coins, amount - coins[ind], ind));
        }

        return res;
    }

    int coinChange(vector<int>& coins, int amount) {
        int res = helper(coins, amount, 0);
        return (res == INT_MAX - 1) ? -1 : res;
    }
};

//Solution 2 - Memoization

class Solution {
public:
    int helper(vector<int>& coins, int amount, int ind, vector<vector<int>>& dp) {
        if(amount == 0) return 0;
        if(amount < 0 || ind >= coins.size()) return INT_MAX-1;

        if(dp[ind][amount] != -1) return dp[ind][amount];

        //exc
        int res = helper(coins, amount, ind+1, dp);

        //inc
        if(coins[ind] <= amount) {
            res = min(res, 1 + helper(coins, amount - coins[ind], ind, dp));
        }

        return dp[ind][amount] = res;
    }

    int coinChange(vector<int>& coins, int amount) {
        vector<vector<int>> dp(coins.size(), vector<int> (amount+1, -1));
        int res = helper(coins, amount, 0, dp);
        return (res == INT_MAX - 1) ? -1 : res;
    }
};

//Solution 3 - Bottom Up DP

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();
        vector<vector<int>> dp(n+1, vector<int> (amount+1, 0));

        for(int j = 1; j<= amount; j++)
            dp[0][j] = INT_MAX - 1;

        for(int i = 1; i<= n; i++) {
            for(int j = 1; j<= amount; j++) {
                if(coins[i-1] > j)
                    dp[i][j] = dp[i-1][j];
                else dp[i][j] = min(dp[i-1][j], 1+ dp[i][j-coins[i-1]]);
            }
        }

        return dp[n][amount] == INT_MAX -1 ? -1 : dp[n][amount];
    }
};