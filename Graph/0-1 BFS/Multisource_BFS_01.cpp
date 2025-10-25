#define F first 
#define S second

using state = pair<int, int>;

int n, m;
vector<string> arr;
vector<vector<vector<int>>> dis;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};

bool is_valid(int x, int y) {
    return (x>=0 && x<n && y>=0 && y<m && arr[x][y]!='#');
}

// Multi-source 0-1 BFS from all 3 components
void multi_BFS_01(char ch) {
    deque<state> dq;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            if(arr[i][j] == ch) {
                dis[ch-'0'][i][j] = 0;
                dq.push_back({i,j});
            }
        }
    }
    
    while(!dq.empty()) {
        state node = dq.front(); 
        dq.pop_front();
        
        for(int k=0; k<4; k++) {
            int nx = node.F + dx[k], ny = node.S + dy[k];
            if(is_valid(nx, ny) && dis[ch-'0'][nx][ny] == 1e9) {
                // cost 0 for moving inside connected components, 1 for moving outside them
                dis[ch-'0'][nx][ny] = dis[ch-'0'][node.F][node.S] + (arr[nx][ny]=='.' ? 1 : 0);
                
                if(arr[nx][ny] == '.') dq.push_back({nx,ny});
                else dq.push_front({nx, ny});
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    
    cin >> n >> m;
    arr.resize(n);
    for(int i=0; i<n; i++) {
        arr[i].resize(m);
        for(int j=0; j<m; j++) {
            cin >> arr[i][j];
        }
    }
    dis.assign(4, vector<vector<int>>(n, vector<int>(m, 1e9)));
    
    // run multi-source BFS from each group of connected components (1,2,3)
    for(char ch='1'; ch<='3'; ch++) multi_BFS_01(ch);
    
    int ans = 1e9;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            // check if cell (i,j) is reachable from all 3 connected components (1,2,3)
            if(arr[i][j]!='#' && dis[1][i][j]!=1e9 && dis[2][i][j]!=1e9 && dis[3][i][j]!=1e9) {
                int road_cnt = (dis[1][i][j] + dis[2][i][j] + dis[3][i][j] - 2*(arr[i][j] == '.'));
                ans = min(ans, road_cnt);
            }
        }
    }
    cout << (ans==1e9 ? -1 : ans) << '\n';
    
    return 0;
}
