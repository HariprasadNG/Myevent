#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<map>
using namespace std;
//Not working solution. Need to work on this.
int solve(set<int> &c, vector<int> &s, int n) {
    if ( n == 0) return 1;
    if (n < *(c.begin())) return 0;
    if (s[n] != -1) return s[n];
    int p = 0;
    for(auto x:c) {
        int t = solve(c, s, n - x);
        if (t > 0) p += t;
    }
    s[n] = p;
    return p;
}
//Recursive solution Needs memoization
int sol[51][251];
int solve2(vector<int> &c, int s,  int n) {
    if ( s == c.size()) return 0;
    if ( n == 0) return 1;
    if ( n < 0 ) return 0;
    if (sol[s][n] != -1) return sol[s][n];
    int x = solve2(c, s, n - c[s]) + solve2(c, s+1, n);
    if (sol[s][n] == -1 ) sol[s][n] = x;
    return x;
}

int main() {
    int cn, n;
    int temp;
    cin >> n;
    cin >> cn;
    vector<int> c;
    vector<int> s;
    for (int i = 0 ; i < 51; i++) {
        for (int j = 0; j < 251; j++) {
            sol[i][j] = -1;
        }
    }
    for (int i = 0; i < cn; i++) {
        cin >> temp;
        c.push_back(temp);
    }
    for (int i = 0; i <= n; i++) {
        s.push_back(-1);
    }
    cout << solve2(c, 0, n) << endl;
    return 0;

    for (auto x: s) {
        cout << x << " ";
    }
    cout << endl;
}

