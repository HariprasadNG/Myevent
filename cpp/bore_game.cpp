#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
#include<numeric>
#include<map>

using namespace std;
typedef unsigned int uint;

int max_point_dp(vector<pair<int,int>> &f) {
    vector<vector<int>> dp(f.size(), vector<int>(f.size(), 0));
    for (int i = 0; i < f.size(); i++) {
        dp[i][i] = f[i].first * f[i].second;
    }
    for (int l = 2; l <= f.size(); l++) {
        for (int i = 0; i <= f.size() - l; i++) {
            int maxT = 0;
            for (int x=i; x < i+l; x++) {
                int t = f[x].first * f[x].second;
                if (x - 1 >= i) {
                    if (f[x-1].first + 1 == f[x].first) {
                        if (x - 2 >= i) {
                            t += dp[i][x-2];
                        }
                    } else {
                        t += dp[i][x - 1];
                    }
                }

                if (x + 1 < i + l) {
                    if (f[x + 1].first - 1 == f[x].first) {
                        if (x + 2 < i + l) {
                            t += dp[x + 2][i + l - 1];
                        }
                    } else {
                        t += dp[x+1][i+l-1];
                    }
                }
                maxT = max (t, maxT);
            }
            dp[i][i+l-1] = maxT;
        }
    }
    return dp[0][f.size() -1];
}
int max_point (map<int, int> &f) {
    int maxS = 0;
    int tM1 = -1;
    int tP1 = -1;
    for (auto x : f) {
       if (x.second == 0) continue;
       if (f.find(x.first - 1) != f.end() ) {
           tM1 = f[x.first - 1];
           f[x.first - 1] = 0;
       }
       if (f.find(x.first + 1) != f.end() ) {
           tP1 = f[x.first + 1];
           f[x.first + 1] = 0;
       }
       f[x.first] = 0;
       int cs = max_point(f);
       if ((cs + x.first * x.second) > maxS) {
           maxS = cs + x.first * x.second;
       }
       if (tM1 != -1) {
           f[x.first - 1] = tM1;
           tM1 = -1;
       }
       if (tP1 != -1) {
            f[x.first + 1] = tP1;
            tP1 = -1;
       }
       f[x.first] = x.second;
    }
    return maxS;
}

int main () {
   map<int, int> ip;
   ip.emplace(1,2);
   ip.emplace(2,5);
   ip.emplace(3,2);


   map<int, int> ip2;
   ip2.emplace(2,2);
   ip2.emplace(3,2);
   ip2.emplace(4,1);
   ip2.emplace(5,1);
   ip2.emplace(7,1);
   vector<pair<int,int>> vip = {{1,2}, {2,5}, {3,2}};
   vector<pair<int, int>> vip2 = {{2,2},{3,2},{4,1},{5,1},{7,1}};
   vector<pair<int, int>> vip3 = {{1,4}, {2,2}, {3,1}, {4,1}, {5,2}};
   cout << max_point(ip2) << endl;
   cout << max_point_dp(vip3) << endl;
}
