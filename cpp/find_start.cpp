#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
#include<numeric>

using namespace std;
typedef unsigned int uint;

//Find the satrt of the rotated of a sorted array.

int findStart(vector<int> a) {
    int s = 0;
    int e = a.size() - 1;
    int m = s + (e-s)/2;
    while (m >= s && m <= e) {
        if (a[m] <= a[e]) {
            e = m - 1;
        } else {
            if (m < (e-1)) {
                if (a[m+1] < a[m]) return m+1;
            }
            s = m + 1;
        }
        m = s + (e-s)/2;
    }
    
    return m;
}

int bs (vector<int> a, int x) {
    int s = 0;
    int e = a.size() -1;
    int m = s + (e - s)/2;
    while (m <= e && m >= s) {
        if (a[m] == x) {
            return m;
        } else if (a[m] < x) {
            s = m + 1;
        } else {
            e = m - 1;
        }
        m = s + (e - s)/2;
    }
    return -1;
}

int main () {
    vector<int> a = {1,2,3,4,5,6,7};
    cout << findStart(a) << endl;
    cout << bs(a, 1) << " " << bs(a, 3) << " " << bs(a, 5) << " " << bs(a, 7) << " " << bs(a, 10) << endl;
}
