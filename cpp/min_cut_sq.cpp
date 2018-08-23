#include <iostream>
#include <vector>
using namespace std;
using uint = unsigned int;
#define A_C_B(A, B) \
    if (A > B) {\
        uint temp_A = A;\
        A = B;\
        B = temp_A;\
    }

uint minCutSq(uint x, uint y) {
    if ( x == y) return 0;
    if ( x == 0 || y == 0) return 0;
    uint t = y/x;
    uint t_x = y % x;
    cout << t << " (" << x << "," << y << ")" << endl;
    if ( t_x == 0) return t - 1;
    y = x;
    x = t_x;
    t += minCutSq(x, y);
    return t;
}

uin minSq(uint x, uint y) {
    vector<vector<uint>> dp;
    for (uint i = 0; i < y; i++) {
        dp[i].push_back({});
        for (uint j = 0; j < y;j++) {
            if(i == j)
                dp[i].push_back(1);
            else
                dp[i].push_back(200000);
        }
    }

    for (uint i = 1; i < y; i++ ) {
        for (uint j = i+1; i < y; j++) {
            if 
        }
    }
}

int main () {
    int T;
    cin >> T;
    while(T--) {
        uint x;
        uint y;
        cin >> x >> y;
        A_C_B(x, y);
        cout << minCutSq(x, y) << endl;
    }
}
