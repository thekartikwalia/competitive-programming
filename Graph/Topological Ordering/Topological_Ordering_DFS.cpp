// O(V + E) --> visits each vertex and edge once
void dfs(int node) {
    vis[node] = 1;                // mark node as visited
    for (auto v : g[node]) {      // explore all outgoing edges
        if (!vis[v]) dfs(v);
    }
    topo.push_back(node);         // add after exploring all children
}

// O(V + E) --> reverse gives valid topological order
void topological_ordering() {
    reverse(topo.begin(), topo.end());    // reverse postorder = topo order
}
