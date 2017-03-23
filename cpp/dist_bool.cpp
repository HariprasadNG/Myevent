#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

int Bfs(vector<vector<int>> &v, pair<int, int> d) {
    if (v[d.first][d.second] == 0) return -1;
    if(v[0][0] == 0) return -1;
    if (d.first == 0 && d.second == 0) return 0;
    queue<pair<int,int>> q;
    vector<vector<int>> visited;

    for (int i = 0; i < v.size(); i++) {
        visited.push_back({});
        for (int j = 0; j < v[i].size(); j++) {
            visited[i].push_back(0);
        }
    }
    q.push({0,0});
    visited[0][0] = true;

    vector<pair<int,int>> dir;
    dir.push_back({0,-1});
    dir.push_back({-1,0});
    dir.push_back({0,1});
    dir.push_back({1,0});

    while(!q.empty()) {
        pair<int,int> s = q.front();
        q.pop();

        for (auto x:dir) {
            int cr = s.first + x.first;
            int cc = s.second + x.second;
            if ( cr < v.size() &&
                 cr >= 0 &&
                 cc < v[cr].size() &&
                 cc >= 0 && 
                 v[cr][cc] &&
                 !visited[cr][cc]) {
                 q.push({cr, cc});
                 visited[cr][cc] = visited[s.first][s.second] + 1;
                 if ( cr == d.first && cc == d.second) return visited[cr][cc] - 1;
            }
        }
    }
    return -1;
}

int main () {
    int T;
    cin >> T;
    while(T--) {
        int r, c;
        cin >> r >> c;

        vector<vector<int>> v;
        for (int i = 0; i < r; i++) {
            v.push_back({});
            for (int j = 0; j < c; j++) {
                int temp;
                cin >> temp;
                v[i].push_back(temp);
            }
        }
        
        int dr, dc;
        cin >> dr >> dc;
        cout << Bfs(v, {dr,dc}) << endl;
    }
}
