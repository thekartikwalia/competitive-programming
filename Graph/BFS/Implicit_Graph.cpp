#define F first 
#define S second

using state = pair<int, int>;     // represents node of graph
const int INF = 1e9;

int n, m;
state st, en;
vector<vector<char>> arr;
vector<vector<int>> dis;          // stores min distance from source
vector<vector<state>> par;        // parent array (for path reconstruction)

// check if (x, y) is inside grid and not a wall
bool is_valid(int x, int y) {
    return (x>=0 && x<n  && y>=0 && y<m && arr[x][y]!='#');
}

int dx[] = {0, 1, -1, 0};
int dy[] = {-1, 0, 0, 1};

// returns valid neighbours of a cell
vector<state> get_neighbours(state node) {
    vector<state> neighs;
    for (int k=0; k<4; k++) {
        int x = node.F + dx[k], y = node.S + dy[k];
        if (is_valid(x, y)) neighs.push_back({x, y});
    }
    return neighs;
}

// O(V + E) ~ O(N * M) --> BFS on grid
void bfs(state sc_node) {
    queue<state> q;
    dis[sc_node.F][sc_node.S] = 0;
    q.push(sc_node);

    while (!q.empty()) {
        state node = q.front(); q.pop();
        for (state v : get_neighbours(node)) {
            if (dis[v.F][v.S] > dis[node.F][node.S] + 1) {
                dis[v.F][v.S] = dis[node.F][node.S] + 1;
                par[v.F][v.S] = node;      // store parent for path reconstruction
                q.push(v);
            }
        }
    }
}

// deduce direction of move between two cells
char get_move(state prev, state curr) {
    if (curr.S == prev.S - 1) return 'L';
    if (curr.S == prev.S + 1) return 'R';
    if (curr.F == prev.F - 1) return 'U';
    return 'D';
}

// reconstruct and print path from A to B
void print_path(state en) {
    vector<state> path;
    state temp = en;

    while(temp != make_pair(-1, -1)) {    // trace back using parent array
        path.push_back(temp);
        temp = par[temp.F][temp.S];
    }
    reverse(path.begin(), path.end());    // reverse bcoz we started from end

    for (int i = 1; i < (int)path.size(); i++)
        cout << get_move(path[i - 1], path[i]);
}

signed main() {
    cin >> n >> m;
    arr.resize(n);
    for(int i=0; i<n; i++) {
        arr[i].resize(m);
        for (int j=0; j<m; j++) {
            cin >> arr[i][j];
            if (arr[i][j] == 'A') st = {i, j};
            else if (arr[i][j] == 'B') en = {i, j};
        }
    }
    dis.assign(n, vector<int>(m, INF));
    par.assign(n, vector<state>(m, {-1, -1}));

    bfs(st);

    if(dis[en.F][en.S] == INF) cout << "NO\n";            // unreachable
    else {
        cout << "YES\n";
        cout << dis[en.F][en.S] << '\n';                  // shortest distance
        print_path(en);                                   // shortest path
    }
}
