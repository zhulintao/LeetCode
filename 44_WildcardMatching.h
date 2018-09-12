/*
Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*'.
'?' Matches any single character.
'*' Matches any sequence of characters (including the empty sequence).
The matching should cover the entire input string (not partial).
Note:
s could be empty and contains only lowercase letters a-z.
p could be empty and contains only lowercase letters a-z, and characters like ? or *.
Example 1:
Input:
s = "aa"
p = "a"
Output: false
Explanation: "a" does not match the entire string "aa".
Example 2:
Input:
s = "aa"
p = "*"
Output: true
Explanation: '*' matches any sequence.
Example 3:
Input:
s = "cb"
p = "?a"
Output: false
Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.
Example 4:
Input:
s = "adceb"
p = "*a*b"
Output: true
Explanation: The first '*' matches the empty sequence, while the second '*' matches the substring "dce".
Example 5:
Input:
s = "acdcb"
p = "a*c?b"
Output: false
*/
// Solution1: 
/*class Solution {
public:
    bool isMatch(string s, string p) {
        int len1 = s.length(), len2 = p.length();
        int i = 0, j = 0, a = 0, b = -1;  // b save the next index of '*'
        while(i < len1)
        {
            if(p[j] == '*')
            {
                while(p[j] == '*') ++j;
                if(j == len2) return true;
                a = i;
                b = j;
            }
            if(p[j] == '?' || s[i] == p[j])
            {
                ++i;
                ++j;
            }
            else
            {
                if(b != -1)
                    i = ++a, j = b;
                else
                    return false;
            }
        }
        while(p[j] == '*') ++j;
        return i == len1 && j == len2;
    }
};*/

// Solution2: Dynamic Programming
class Solution {
public:
    bool isMatch(string s, string p)
    {
        //vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, false));
        bool dp[s.size() + 1][p.size() + 1];
        memset(dp, false, sizeof(bool) * (s.size() + 1) * (p.size() + 1));
        dp[0][0] = true;
        for(int i = 1; i <= p.size(); i++)
        {
            if(p[i - 1] == '*')
                dp[0][i] = dp[0][i - 1];
        }
        for(int i = 1; i <= s.size(); i++)
        {
            for(int j = 1; j <= p.size(); j++)
            {
                if(s[i - 1] == p[j - 1] || p[j - 1] == '?')
                    dp[i][j] = dp[i - 1][j - 1];
                else if(p[j - 1] == '*')
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
            }
        }
        return dp[s.size()][p.size()];
    }
};
