vector<vector<int>> g;
vector<int> indeg;
vector<int> topo;

// O(V + E) --> Kahn's Algorithm (BFS-based Topological Sort)
void kahn() {
    queue<int> q;
    for(int i=1; i<=n; i++) {
        if(indeg[i]==0) q.push(i);
    }
    while(!q.empty()) {
        int node = q.front(); 
        q.pop();
        topo.push_back(node);
        for(auto v:g[node]) {
            indeg[v]--;
            if(indeg[v]==0) {
                q.push(v);
            }
        }
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    g.resize(n+1);
    indeg.assign(n+1,0);
    for(int i=0; i<m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        indeg[b]++;
    }

    kahn();

    // if not all nodes included -> graph has a cycle
    if(topo.size() != n) {
        cout << "There's a cycle\n";
    } else {
        for(auto v:topo) cout << v << " ";
        cout << '\n';
    }
}
