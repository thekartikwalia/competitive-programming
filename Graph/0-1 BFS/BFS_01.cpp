#define F first 
#define S second

// O(V + E) --> each node/edge processed at most twice
void BFS_01(int sc_node) {
    deque<int> dq;

    dis[sc_node] = 0;
    dq.push_back(sc_node);

    while (!dq.empty()) {
        int node = dq.front(); 
        dq.pop_front();

        for (auto v : g[node]) {
            int neigh = v.F, wt = v.S;
            if (dis[neigh] > dis[node] + wt) {    // relax edge if shorter path found
                dis[neigh] = dis[node] + wt;

                // 0-weight edges -> front, 1-weight -> back to maintain BFS invariant property
                if (wt == 0) dq.push_front(neigh);
                else dq.push_back(neigh);
            }
        }
    }
}
