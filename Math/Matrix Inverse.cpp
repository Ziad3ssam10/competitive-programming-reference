vector <vector <ld>> inverse(vector <vector <ld>> mt)
{
    int n = mt.size();
    vector <vector <ld>> ans(n, vector <ld> (n));
    for(int i = 0; i < n; i++)
        ans[i][i] = 1;
    for(int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (mt[j][i] > mt[i][i]) {
                mt[j].swap(mt[i]);
                ans[j].swap(ans[i]);
            }
        }
        ld val = mt[i][i];
        
        for(int j = 0; j < n; j++)
            mt[i][j] /= val, ans[i][j] /= val;
        
        for(int j = 0; j < n; j++)
        {
            if(j == i)
                continue;
            val = mt[j][i];
            for(int k = 0; k < n; k++)
            {
                mt[j][k] -= val * mt[i][k];
                ans[j][k] -= val * ans[i][k];
            }
        }
    }
    return ans;
}
