#include <iostream>
#include <vector>
#include <utility>
using namespace std;

int Coverage(pair<int,int> n, int r, int c) {
    vector<pair<int,int>> m;
    m.push_back({0,0});
    m.push_back({-2, -1});
    m.push_back({-2, 1});
    m.push_back({2, -1});
    m.push_back({2, 1});
    m.push_back({1, 2});
    m.push_back({1, -2});
    m.push_back({-1, 2});
    m.push_back({-1, 2});

    int count = 0;
    for (auto x: m) {
        if (n.first + x.first >= 0 &&
            n.first + x.first < r &&
            n.second + x.second >= 0 &&
            n.second + x.second < c) count++;
    }

    return count;
}

int solve(int m, int n) {
    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            count += m*n - Coverage({i,j}, m, n);
        }
    }
    return count;
}


int main () {
    int T;
    cin >> T;
    while(T--) {
        int m, n;
        cin >> m >> n;
        cout << solve(m ,n) << endl;
    }
}
