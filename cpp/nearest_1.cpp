#include<iostream>
#include<queue>
#include<utility>
#include<limits>
using namespace std;

int Mat[20][20];
int sol[20][20];

void solve (int n, int m) {
    queue<pair<int,int>> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if(sol[i][j] == 0){
                q.push({i,j});
            }
        }
    }

    while (!q.empty()) {
       auto top = q.front();
       q.pop();
       if (top.first > 0) {
            if(sol[top.first - 1][top.second] > sol[top.first][top.second] + 1) {
                sol[top.first - 1][top.second] = sol[top.first][top.second] + 1;
                q.push({top.first - 1, top.second});
            }
       }
       if (top.second > 0) {
            if(sol[top.first][top.second - 1] > sol[top.first][top.second] + 1) {
                sol[top.first][top.second - 1] = sol[top.first][top.second] + 1;
                q.push({top.first, top.second - 1});
            }
       }
       if (top.first + 1 <  m) {
            if(sol[top.first + 1][top.second] > sol[top.first][top.second] + 1) {
                sol[top.first + 1][top.second] = sol[top.first][top.second] + 1;
                q.push({top.first + 1, top.second});
            }
       }
       if (top.second + 1 < n) {
            if(sol[top.first][top.second +1] > sol[top.first][top.second] + 1) {
                sol[top.first][top.second + 1] = sol[top.first][top.second] + 1;
                q.push({top.first, top.second + 1});
            }
       }
    }
}

int main() {
    int t;
    cin >> t;
    while(t) {
        t--;

        int m, n;
        cin >> m >> n;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
               int temp;
               cin >> temp;
               if(temp) {
                    sol[i][j] = 0;
               } else {
                sol[i][j] = numeric_limits<int>::max();
               }
            }
        }

        solve(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << sol[i][j] << " ";
            }
        }
        cout << endl;
    }
}

