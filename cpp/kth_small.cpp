#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int kth_small(vector<int> &v, int k, int s, int e) {
    int p = s;
    int i = s + 1;
    int j = e;

    while (i < j) {
        if (v[i] <= v[p]) {
            i++;
        } else {
            while ( j > i &&
                    v[--j] > v[p]);
            if ( j == i) break;
            int temp = v[i];
            v[i] = v[j];
            v[j] = temp;
        }
    }

    int temp = v[i-1];
    v[i-1] = v[p];
    v[p] = temp;

    if ( k == i-1) {
        return v[i-1];
    } else if( k > i - 1) {
        return kth_small(v, k, i, e);
    } else {
        return kth_small(v, k, s, i-1);
    }
}

int main () {
    int T;
    cin >> T;
    while(T--) {
        int n;
        cin >> n;
        vector<int> v;
        while (n--) {
            int temp;
            cin >> temp;
            v.push_back(temp);
        }
        int k;
        cin >> k;
        //cout << kth_small(v, k-1, 0, v.size()) << endl;
        nth_element(v.begin(), v.begin() + k - 1, v.end());
        cout << v[k-1] << endl;
    }
}
