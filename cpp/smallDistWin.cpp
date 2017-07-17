#include <iostream>
#include <vector>
#include <string>
#include <string.h>
typedef unsigned int uint;
using namespace std;

class Data {
    public:
        bool uq[26];
        int count;
        Data() {
            memset(uq, 0, sizeof(uq));
            count = 0;
        }
};

int uqWin(string s) {
    vector<vector<Data>> v;
    int sm = 1;
    int maxUqCount = 1;
    for (unsigned int i = 0; i < s.size(); i++ ) {
        v.push_back(vector<Data>());
        for (unsigned int j = 0; j < s.size(); j++) {
            Data d;
            if (i == j) {
                d.uq[s[i] - 'a'] = true;
                d.count = 1;
            }
            v[i].push_back(d);
        }
    }

    for (int i = 0; i < s.size(); i++) {
        for (int j = i+1; j < s.size(); j++) {
            memcpy(v[i][j].uq, v[i][j-1].uq, sizeof(v[i][j].uq));
            v[i][j].count = v[i][j-1].count;

            if (!v[i][j].uq[s[j] - 'a']) {
                v[i][j].uq[s[j] - 'a'] = true;
                v[i][j].count++;
                if ( maxUqCount < v[i][j].count) {
                    sm = j - i + 1;
                    maxUqCount = v[i][j].count;
                } else if (maxUqCount == v[i][j].count) {
                    sm = ((j - i + 1) < sm) ? (j - i + 1) : sm;
                }
            }
        }
    }

    return sm;
}

int main () {
    int T;
    cin >> T;
    while(T--) {
        string s;
        cin >> s;
        cout << uqWin(s) << endl;
    }
}
