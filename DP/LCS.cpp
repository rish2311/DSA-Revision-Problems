// https://leetcode.com/problems/longest-common-subsequence

// Solution 1 - Recursion TLE (indices from n, m to 0)
// Time Complexity - O(2^(n+m)) - exponential
// Space Complexity -  O(n+m) - linear

class Solution {
public:
    int helper(string text1, string text2, int ind1, int ind2) {
        if(ind1 < 0 || ind2 < 0)
            return 0;
        if(text1[ind1] == text2[ind2]) 
            return 1 + helper(text1, text2, ind1-1, ind2-1);
        return max(helper(text1, text2, ind1-1, ind2), helper(text1, text2, ind1, ind2-1));
    }

    int longestCommonSubsequence(string text1, string text2) {
        return helper(text1, text2, text1.size()-1, text2.size()-1);
    }
};

// Solution 2 - Memoization (indices from n, m to 0)
// Time Complexity - O(nm) - no of unique function calls
// Space Complexity -  O(n+m) + O(nm) (recursive stack space + 2d array)

class Solution {
public:
    int helper(string& text1, string& text2, int ind1, int ind2, vector<vector<int>>& dp) {
        if(ind1 < 0 || ind2 < 0)
            return 0;
        if(dp[ind1][ind2] != -1) return dp[ind1][ind2];
        if(text1[ind1] == text2[ind2]) 
            return dp[ind1][ind2] = 1 + helper(text1, text2, ind1-1, ind2-1, dp);
        return dp[ind1][ind2] = max(helper(text1, text2, ind1-1, ind2, dp), 
                                    helper(text1, text2, ind1, ind2-1, dp));
    }

    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size(), vector<int> (text2.size(), -1));
        return helper(text1, text2, text1.size()-1, text2.size()-1, dp);
    }
};

// Solution 3 - Recursion - TLE (indices from 0 to n, m)
// Time Complexity - O(2^(m+n)) - exponential
// Space Complexity -  O(n+m) - linear

class Solution {
public:
    int helper(string text1, string text2, int ind1, int ind2) {
        if(ind1 >= text1.length() || ind2 >= text2. length())   
            return 0;

        if(text1[ind1] == text2[ind2]) return 1 + helper(text1, text2, ind1 +1, ind2+1);

        return max(helper(text1, text2, ind1+1, ind2), helper(text1, text2, ind1, ind2+1));
    }

    int longestCommonSubsequence(string text1, string text2) {
        return helper(text1, text2, 0, 0);
    }
};

// Solution 4 - Memoization (indices from 0 to n)
// Time Complexity - O(nm) - no of unique function calls
// Space Complexity -  O(n+m) + O(nm) (recursive stack space + 2d array)

class Solution {
public:
    int helper(string& text1, string& text2, int ind1, int ind2, vector<vector<int>>& dp) {
        if(ind1 >= text1.length() || ind2 >= text2. length())   
            return 0;

        if(dp[ind1][ind2] != -1) return dp[ind1][ind2];

        if(text1[ind1] == text2[ind2]) 
            return dp[ind1][ind2] = 1 + helper(text1, text2, ind1 +1, ind2+1, dp);

        return dp[ind1][ind2] = max(helper(text1, text2, ind1+1, ind2, dp), 
                                    helper(text1, text2, ind1, ind2+1, dp));
    }

    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size(), vector<int> (text2.size(), -1));
        return helper(text1, text2, 0, 0, dp);
    }
};

// Solution 5 - Bottom-Up DP
// Time Complexity - O(nm) 
// Space Complexity -  O(nm) 

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));

        for(int i = 1; i<=n; i++) {
            for(int j = 1; j<=m; j++) {
                if(text1[i-1] == text2[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }

        return dp[n][m];
    }
};

// Solution 6 - Space Optimised Bottom Up DP
// Time Complexity - O(nm) 
// Space Complexity -  O(m) 

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int n = text1.size(), m = text2.size();
        vector<int> prev(m+1, 0);
        vector<int> curr(m+1, 0);

        for(int i = 1; i<=n; i++) {
            for(int j = 1; j<=m; j++) {
                if(text1[i-1] == text2[j-1])
                    curr[j] = 1 + prev[j-1];
                else curr[j] = max(prev[j], curr[j-1]);
            }
            prev = curr;
        }
        return curr[m];
    }
};