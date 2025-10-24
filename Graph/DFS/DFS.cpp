// O(V + E) --> visits each vertex and edge once
void dfs(int node) {
    vis[node] = 1;              // mark current node as visited
    for (auto v : g[node]) {    // explore all adjacent nodes
        if (!vis[v]) {          // if not visited, go deeper
            dfs(v);
        }
    }
}
