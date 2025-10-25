// O(V + E) --> Kahn's Algorithm (BFS-based Topological Sort)
void kahn() {
    queue<int> q;

    // push all nodes with indegree 0
    for(int i=1; i<=n; i++) {
        if(indeg[i]==0) q.push(i);
    }

    while(!q.empty()) {
        int node = q.front(); 
        q.pop();
        topo.push_back(node);    // add to topo order

        for(auto v:g[node]) {    // reduce indegree of neighbours
            indeg[v]--;
            if(indeg[v]==0) {    // if indegree becomes 0, push it
                q.push(v);
            }
        }
    }
}
