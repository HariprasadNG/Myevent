#include<iostream>
#include<utility>
#include<algorithm>
using namespace std;
#define UPDATE_FROM_ROW(x,y) \
    mat[x][y].first = min(mat[x-1][y].second + ip[x][y], mat[x-1][y].first);\
    mat[x][y].second = mat[x-1][y].second + ip[x][y];

#define UPDATE_FROM_COL(x,y) \
    mat[x][y].first = min(mat[x][y-1].second + ip[x][y], mat[x][y-1].first);\
    mat[x][y].second = mat[x][y-1].second + ip[x][y];

int ip[10][10];

int ComputeMinDis(int r, int c) {
    pair<int, int> mat[10][10];
    mat[0][0].first = ip[0][0];
    mat[0][0].second = ip[0][0];
    for (int i = 0 ; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if ((i-1) >= 0 && (j-1) >= 0) {
                if (mat[i][j-1] < mat[i-1][j]) {
                    UPDATE_FROM_ROW(i,j);
                } else {
                    UPDATE_FROM_COL(i,j);
                }
            } else if ((i - 1) >= 0) {
                UPDATE_FROM_ROW(i,j);
            } else if ((j - 1) >= 0){
                UPDATE_FROM_COL(i,j);
            }
        }
    }
    if (mat[r-1][c-1].second <= 0) {
        return (mat[r-1][c-1].first * -1) + 1;
    } else {
        return max(mat[r-1][c-1].first * -1, 1);
    }
}

int ReadIp(int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> ip[i][j];
        }
    }
}

int main () {
    int t;
    cin >> t;
    for (int i = 0 ; i < t; i++) {
        int r;
        int c;
        cin >> r;
        cin >> c;
        ReadIp(r,c);
        cout << ComputeMinDis(r,c) << endl;
    }
}
