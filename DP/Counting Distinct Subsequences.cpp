dp[0] = 1; 
// Traverse through all lengths from 1 to n.
 for (int i = 1; i <= n; i++) 
{ 
    dp[i] = (2 * dp[i - 1]) % md; 
// If current character has appeared 
// before, then remove all subsequences 
// ending with previous occurrence. 
if (last[str[i - 1]] != -1) 
        dp[i] = (dp[i] - dp[last[str[i - 1]]] + md) % md; 
// Mark occurrence of current character 
    last[str[i - 1]] = (i - 1); 
} 
return dp[n]; // dp[n] - 1 to remove empty subsequence
