#include <iostream>
#include <vector>
#include <string>
#include <set>
using namespace std;

int lcs(string a, string b) {
    vector<vector<set<string>>> max;
    for(int i = 0 ; i < a.length(); i++) {
        if (max.size() < i + 1) {
            vector<set<string>> t;
            max.push_back(t);
        }
        for (int j = 0; j < b.length(); j++) {
            if(max[i].size() < j + 1) {
                set<string> t;
                max[i].push_back(t);
            }
            if (a[i] == b[j]) {
                if (i - 1 >= 0 && j - 1 >= 0) {
                   if(max[i-1][j-1].size() > 0) {
                       for (auto x: max[i-1][j-1]) {
                           max[i][j].emplace(x + a[i]);
                       }
                   } else {
                       string t(1, a[i]);
                       max[i][j].emplace(t);
                   }
                } else {
                    string t(1,a[i]);
                    max[i][j].emplace(t);
                }
            } else {
                if (i - 1 >= 0 && j - 1 >= 0) {
                    if (max[i-1][j].size() && max[i][j-1].size()) {
                        if (max[i-1][j].begin()->length() > max[i][j-1].begin()->length()) {
                            max[i][j] = max[i-1][j];
                        } else if (max[i-1][j].begin()->length() == max[i][j-1].begin()->length()) {
                            max[i][j] = max[i-1][j];
                            for (auto x: max[i][j-1]) {
                                max[i][j].emplace(x);
                            }
                        } else {
                            max[i][j] = max[i][j-1];
                        }
                    } else if (max[i-1][j].size() > 0) {
                        max[i][j] = max[i-1][j];
                    } else {
                        max[i][j] = max[i][j-1];
                    }
                } else if (i - 1 >= 0) {
                    max[i][j] = max[i-1][j];
                } else if (j -1 >= 0) {
                    max[i][j] = max[i][j-1];
                }
            }
        }
    }
    for (auto x: max[a.size() - 1][b.size() - 1]) {
        cout << x << " ";
    }
    if (max[a.size() - 1][b.size() - 1].size() == 0) return 0;
    return max[a.size() - 1][b.size() - 1].begin()->length();
}


int main () {
    int T;
    cin >> T;
    while(T--) {
        string a, b;
        cin >> a;
        cin >> b;
        lcs(a,b);
        cout << endl;
    }
}
