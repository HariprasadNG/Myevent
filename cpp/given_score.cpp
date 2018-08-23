#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
#include<numeric>

using namespace std;
typedef unsigned int uint;

int ways_score(vector<int> c, int s) {
    vector<int> r(s+1, 0);
    r[0] = 0;
    for (int i = 1; i <= s; i++) {
        for (auto x:c) {
            if ( (i-x) > 0) {
                r[i] += r[i-x];
            } else if ( i == x) {
                r[i] = 1;
            }
        }
    }
    return r[s];
}

int main () {
    vector<int> c = {3, 5, 10};
    cout << ways_score(c, 22) << endl;
    return 0;
}
