struct SOS {
    vector<ll> dp;
    
    SOS() {
        dp = vector<ll>((1 << LG) + 5, 1);
    }
    
    void forward() {
        //mask takes from it's subsets
        for (int i = 0; i < LG; i++) {
            for (int msk = 0; msk < (1 << LG); msk++) {
                //adding to supermask
                if ((1 << i) & msk)
                    dp[msk] += dp[msk ^ (1 << i)];
            }
        }
    }
    
    void backward() {
        for (int i = 0; i < LG; i++) {
            for (int msk = (1 << LG) - 1; msk >= 0; msk--) {
                if ((1 << i) & msk)
                    dp[msk] -= dp[msk ^ (1 << i)];
            }
        }
    }
    
    void forward2()
    {
        for (int i = 0; i < LG; i++) {
            for (int msk = 0; msk < (1 << LG); msk++) {
                //adding to submask
                if ((1 << i) & msk)
                    dp[msk ^ (1 << i)] += dp[msk];
            }
        }
    }
    
    void backward2()
    {
        for (int i = 0; i < LG; i++) {
            for (int msk = (1 << LG) - 1; msk >= 0; msk--) {
                if ((1 << i) & msk)
                    dp[msk ^ (1 << i)] -= dp[msk];
            }
        }
    }
};
