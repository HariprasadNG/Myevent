#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

int distPal(string s) {
    vector<vector<bool>> pal;
    set<string> res;
    for (int i = 0 ; i < s.size(); i++) {
        pal.push_back(vector<bool>());
        for (int j = 0; j < s.size(); j++) {
            if ( i == j) {
                pal[i].push_back(true);
            } else {
                pal[i].push_back(false);
            }
        }
    }
    for (int i = 1; i < s.size(); i++) {
        if (s[i-1] == s[i]) {
            pal[i-1][i] = true;
        }
    }

    for (int i = 2; i < s.size(); i++) {
        for (int j = 0; j + i <  s.size(); j++) {
            if ( pal[j+1][j + i - 1] && s[j] == s[j + i]) {
                pal[j][j+i] = true;
            }
        }
    }
    for (int i = 0; i < s.size(); i++) {
        for (int j = i; j < s.size(); j++) {
            if (pal[i][j]) {
                string ts = s.substr(i, j - i + 1);
                res.emplace(ts);
            }
        }
    }
   return res.size();
}


int main () {
    int T;
    cin >> T;
    while(T--) {
        string s;
        cin >> s;
        cout << distPal(s) << endl;
    }
}
