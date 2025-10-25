int n, m;
vector<vector<int>> g;

int dp[100100];

// rec(i): returns length of longest path starting at node i
int rec(int node) {    
    if(dp[node] != -1) return dp[node];
    int ans=1;                            // path of at least length 1 (itself)
    for(auto v:g[node]) {
        ans = max(ans, 1+rec(v));         // take best among all outgoing paths
    }
    return dp[node] = ans;
}

signed main() {
    cin >> n >> m;
    g.resize(n+1);
    for(int i=0; i<m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }
    memset(dp, -1, sizeof(dp));

    int max_len=0;
    for(int i=1; i<=n; i++) {
        max_len = max(max_len, rec(i));   // check longest path from each node
    }
    cout << max_len;
}
