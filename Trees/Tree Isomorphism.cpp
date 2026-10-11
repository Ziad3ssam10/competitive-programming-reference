// O(n log n), 1-based nodes, can be O(n) using xor hashing
vector<int> center(vector<vector<int>>& adj){
    int n = adj.size()-1;
    if(n == 1) return {1};
    vector<int> deg(n+1), v;

    for(int i = 1; i <= n; i++){
        deg[i] = adj[i].size();
        if(deg[i] == 1) v.push_back(i), deg[i]--;
    }
    int m = v.size();
    while(m < n){
        vector<int> nv;
        for(auto i : v){
            for(auto j : adj[i]){
                deg[j]--;
                if(deg[j] == 1) nv.push_back(j);
            }
        }
        m += nv.size(), v = nv;
    }
    return v;
}

map<vector<int>, int> mp;
int id;

int dfs(int s, int p, vector<vector<int>>& adj){
    vector<int> v;
    for(auto i: adj[s])
        if(i != p) v.push_back(dfs(i, s, adj));
    
    sort(v.begin(), v.end());
    if(!mp.count(v)) mp[v] = id++;
    return mp[v];
}

bool sameTree(vector<vector<int>>& adj1, vector<vector<int>>& adj2){
    if(adj1.size() != adj2.size()) return false;
    id = 0;
    mp.clear();
    vector<int> v1 = center(adj1), v2 = center(adj2);
    int s1 = dfs(v1[0], v1[0], adj1);
    
    for(auto s : v2){
        int s2 = dfs(s, s, adj2);
        if(s1 == s2) return true;
    }
    return false;
}