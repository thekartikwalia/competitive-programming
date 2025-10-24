// O(V + E) --> each node and edge is processed once
void bfs(int sc_node) {
    queue<int> q;

    dis[sc_node] = 0;    // source node has distance 0
    q.push(sc_node);

    while (!q.empty()) {
        int node = q.front(); 
        q.pop();

        // if(vis[node]) continue;
        // vis[node] = 1;

        for (auto v : g[node]) {
            if (dis[v] > dis[node] + 1) {   // found shorter path, so relax the edge
                dis[v] = dis[node] + 1;     // update distance
                q.push(v);                  // push for further exploration
            }
        }
    }
}

/*
FUN FACT: COMMENTED STEPS ARE OPTIONAL
- In BFS, 'visited' and 'distance' arrays are tightly correlated:
    vis[node] == 0  ⇔  dis[node] == INF
    vis[node] == 1  ⇔  dis[node] != INF
- Hence, only 'dis' array suffices for BFS (unlike 0-1 BFS, Dijkstra, etc.)
- This works because BFS explores in layers of increasing distance.
*/
