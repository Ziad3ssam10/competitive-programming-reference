```cpp
long long dp[20][2][2];   
string num;  
  
long long solve(int idx, bool start, bool tight) {  
    if (idx == num.length()) {  
        return start ? 1 : 0;   
    }  
  
    if (dp[idx][start][tight] != -1) {  
        return dp[idx][start][tight];  
    }  
    int limit = tight ? (num[idx] - '0') : 9;  
    long long ans = 0;  
    for (int d = 0; d <= limit; d++) {  
        bool next_tight = tight && (d == limit);  
        bool next_start = start || (d > 0);  
        ans += solve(idx + 1, next_start, next_tight);  
    }  
    return dp[idx][start][tight] = ans;  
}
```

```cpp
long long dp[20][2][2][2];   
string L, R;  
  
long long solve(int idx, bool start, bool tight_L, bool tight_R) {  
    if (idx == R.length()) {  
        return start ? 1 : 0;   
    }  
  
    if (dp[idx][start][tight_L][tight_R] != -1) {  
        return dp[idx][start][tight_L][tight_R];  
    }  
  
    int min_digit = tight_L ? (L[idx] - '0') : 0;  
    int max_digit = tight_R ? (R[idx] - '0') : 9;  
      
    long long ans = 0;  
    for (int d = min_digit; d <= max_digit; d++) {  
        bool next_tight_L = tight_L && (d == min_digit);  
        bool next_tight_R = tight_R && (d == max_digit);  
        bool next_start = start || (d > 0);  
        ans += solve(idx + 1, next_start, next_tight_L, next_tight_R);  
    }  
    return dp[idx][start][tight_L][tight_R] = ans;  
}
```