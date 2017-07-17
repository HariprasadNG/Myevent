#include <iostream>
#include <vector>
#include <utility>
#include <queue>
typedef unsigned int uint;
using namespace std;

pair<int,int> dir[] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

int explore (vector<vector<int>> &mat, int r, int c) {
    queue<pair<int, int>> Q;
    mat[r][c] = 2;
    Q.push({r,c});
    int count = 1;
    while (!Q.empty()) {
        pair<int, int> c_pos = Q.front();
        for (auto x: dir) {
            if ( c_pos.first + x.first >= 0 &&
                 c_pos.first + x.first < (int)mat.size() &&
                 c_pos.second + x.second >= 0 && 
                 c_pos.second + x.second < (int)mat[0].size() &&
                 (mat[c_pos.first + x.first][c_pos.second + x.second] == 1 ||
                  mat[c_pos.first + x.first][c_pos.second + x.second] == 2)) {
                if (mat [c_pos.first + x.first][c_pos.second + x.second] == 1) {
                    Q.push({c_pos.first + x.first, c_pos.second + x.second});
                    count++;
                }
                mat[c_pos.first + x.first][c_pos.second + x.second] = 2;
            }
            mat[c_pos.first][c_pos.second] = 3;
        }
        Q.pop();
    }
    return count;
}

void printMat(vector<vector<int>> &mat) {
    for (auto r: mat) {
        for (auto c: r) {
            cout << c << " ";
        }
        cout << endl;
    }
}

int maxRegion (vector<vector<int>> &mat) {
    int max = 0;
    for (uint i = 0 ; i < mat.size(); i++) {
        for (uint j = 0; j < mat[i].size(); j++) {
            if (mat[i][j] == 1) {
                int temp = explore(mat, i, j);
                max = temp > max ? temp:max;
            }
        }
    }
    cout << endl;
    //printMat(mat);
    return max;
}

int main () {
    int T;
    cin >> T;
    while(T--) {
        int r, c;
        cin >> r >> c;
        vector<vector<int>> mat;
        for (int i = 0; i < r; i++) {
            mat.push_back({});
            for (int j = 0; j < c; j++) {
                int temp;
                cin >> temp;
                mat[i].push_back(temp);
            }
        }
        cout << maxRegion(mat) << endl;
    }
}
