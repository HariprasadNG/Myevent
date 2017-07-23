#include <iostream>
#include <vector>
#include <utility>
using namespace std;

vector<pair<int, int>> pmv = {{2,-1}, {2,1}, {1,-2}, {1,2}, {-1,-2}, {-1,2}, {-2,-1}, {-2,1}};

int size = 8;

bool isValidPos (pair<int,int> pos) {
    return pos.first >= 0 &&
           pos.first <= size - 1 &&
           pos.second >= 0 &&
           pos.second <= size - 1;
}

int minMoves(pair<int,int> s, pair<int, int> d) {
    int mat[size][size];
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (s == make_pair(i,j)) {
                mat[i][j] = 0;
            } else {
                mat[i][j] = 100000;
            }
        }
    }
    vector<pair<int,int>> n;
    n.push_back(s);
    int cs = 0;
    do {
        if (mat[d.first][d.second] < 100000) {
            return cs;
        }
        vector<pair<int,int>> tn;
        for (auto c : n) {
            for (auto x: pmv) {
                if (isValidPos(make_pair(c.first + x.first, c.second + x.second))) {
                    if (mat[c.first + x.first][c.second + x.second] > (cs + 1) ) {
                        mat[c.first + x.first][c.second + x.second] = cs + 1;
                        tn.push_back(make_pair(c.first + x.first, c.second + x.second));
                    }
                }
            }
        }
        cs = cs + 1;
        n = tn;
    } while(n.size() > 0);

    return -1;
}

int main () {
    int T;
    cin >> T;
    while(T--) {
        cin >> size;
        int x, y;
        cin >> x >> y;
        pair<int, int> s(x-1, y-1);
        cin >> x >> y;
        pair<int, int> d(x-1, y-1);
        cout << minMoves(s, d) << endl;
    }
}
