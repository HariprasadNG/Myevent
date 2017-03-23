#include<iostream>
#include<limits>
#include<stdlib.h>
#include<set>
#include<vector>
using namespace std;

int min_sum_part(vector<int> &v, int sl, int sr, int s) {
    if ( s == v.size()) {
        return abs(sl-sr);
    }
    int d1 = min_sum_part(v, sl + v[s], sr, s+1);
    int d2 = min_sum_part(v, sl, sr + v[s], s+1);
    if (d1 >= d2) {
        return d2;
    } else {
        return d1; 
    }
}

void sumsplit(int sum, int n, vector<int> &r) {
    if (n == 1) {
        for (auto x: r) {
            cout << x << ", ";
        }
        cout << sum <<endl;
        return;
    }

    for (int i = 0; i <= sum; i++) {
        r.push_back(i);
        sumsplit(sum-i, n-1, r);
        r.pop_back();
    }
}

int main () {
    int t;
    cin >> t;
    for (int i = 0;i < t;i++) {
        int n;
        cin >> n;
        vector<int> v;
        for (int j = 0; j < n; j++) {
            int temp;
            cin >> temp;
            v.push_back(temp);
        }
        int sr = 0;
        int sl = 0;
        cout << min_sum_part(v, sl, sr, 0) << endl;
    }
}
