int n, m;
vector<vector<int>> g;
vector<int> vis, topo;

int dp[100100];    // dp[i]: length of longest path starting at node i

void dfs(int node) {
    vis[node] = 1;
    for(auto v:g[node]) {
        if(!vis[v]) dfs(v);  
    }
    topo.push_back(node); 
}

signed main() {
    cin >> n >> m;
    g.resize(n+1);
    for(int i=0; i<m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }
    
    for(int i=1; i<=n; i++) {
        if(!vis[i]) dfs(i); 
    }

    // process in reverse topological order
    int max_len = 0;
    for(auto node:topo) {
        int ans=1;                     // path of at least length 1 (itself)
        for(auto v:g[node]) {
            ans = max(ans, 1+dp[v]);   // take best among all outgoing paths
        }
        dp[node] = ans;
        max_len = max(max_len, dp[node]);
    }
    cout << max_len << '\n';
}
