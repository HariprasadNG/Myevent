#include<iostream>
#include<vector>
#include<limits>

using namespace std;

typedef  unsigned int uint;

int LCIS_mem (vector<int> a) {
    vector<vector<int>> m(a.size(), vector<int>(a.size()));
    vector<vector<int>> pm(a.size(), vector<int>(a.size()));

    for (uint i = 0; i < a.size(); i++) {
        for (uint j = 0; j < a.size(); j++) {
            if (i == j) {
                m[i][j] = 1;
            } else {
                m[i][j] = 0;
            }
            pm[i][j] = numeric_limits<int>::min();
        }
    }

    for (uint i = 1; i < a.size(); i++) {
        for (uint j = 0; j + i < a.size(); j++) {
           int pmfcc = (pm[j][j + i - 1] > a[j + i - 1]) ?  pm[j][j + i - 1] : a[j + i - 1];
           int cmfpc = pmfcc;
            if (a[j + i -1] > a[j + i] && a[j + i] > pmfcc) { // pmfcc < a[j+i] < a[j + i -1]
                m[j][j+i] =  m[j][j + i - 1];
                pm[j][j+i] = pm[j][j + i - 1];
            } else if (a[j +i] > cmfpc) {
                m[j][j+i] = m[j][j + i - 1] + 1;
                pm[j][j+i] = pmfcc;
            } else {
                m[j][j+i] =  m[j][j + i - 1];
                pm[j][j+i] = pmfcc;
            }
        }
    }

    return m[0][a.size() - 1];
    
}

int LCIS(vector<int> a, int ci = 0, int pi = -1) {
    if (ci >= a.size()) return 0;
    int pmin = (pi == -1)?numeric_limits<int>::min():a[pi];
    if (a[ci] >= pmin) {
        int r1 = LCIS(a, ci + 1, ci) + 1; //considering current element.
        int r2 = LCIS(a, ci + 1, pi); //Not considering current element.
        return (r1 > r2)?r1:r2;
    }
    return LCIS(a, ci + 1, pi); //Current element can't be part of LCIS....
}

int main() {
    int e;
    cin >> e;
    vector<int> a;
    while(e--) {
        int x;
        cin >> x;
        a.push_back(x);
    }
    cout << LCIS_mem(a);
}
