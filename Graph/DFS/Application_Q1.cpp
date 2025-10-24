int n, m;
vector<vector<int>> g;
vector<int> vis;    // vis[i] -> stores which component node i belongs to

// O(V + E) --> visits each vertex and edge once
void dfs(int node, int comp_no) {
    vis[node] = comp_no;           // mark node with current component number
    for (auto v : g[node]) {       // explore all adjacent nodes
        if (!vis[v]) {             // if not visited, continue DFS
            dfs(v, comp_no);
        }
    }
}

void solve() {
    // handle case of disconnected components
    int num_comp = 0;              // number of connected components
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            num_comp++;
            dfs(i, num_comp);
        }
    }
    cout << "No. of components : " << num_comp << '\n';

    // group nodes by their component
    vector<vector<int>> components(num_comp + 1);
    for (int i = 1; i <= n; i++) {
        components[vis[i]].push_back(i);
    }

    // print size of each component
    for (int i = 1; i <= num_comp; i++) {
        cout << i << ": " << components[i].size() << '\n';
    }
}
