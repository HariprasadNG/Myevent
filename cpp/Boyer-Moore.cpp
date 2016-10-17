#include<iostream>
#include<map>
#include<set>
#include<vector>
#include<string>
#include<functional>

using namespace std;

auto preProcess(string P) {
    map<char, vector<int> > R;
    for (int i = P.length()-1; i >= 0; i--) {
        R[P[i]].push_back(i);
    }
    return R;
}

vector<int> BoyerMoorExtendBadCharMatch(string T, string P) {
    int pi = P.length() - 1;
    int ti = 0;
    vector<int> R;
    if (T.length() < P.length()) return R;
    auto info = preProcess(P);
    while (ti <= (T.length() - P.length())) {
        if (T[ti + pi] == P[pi]) {
            pi--;
        } else {
            //Use the preprocess info here to shift
            int shift = 1;
            pi--;
            for (auto x = info[T[ti+pi]].begin(); 
                      x != info[T[ti+pi]].end(); x++) {
                if (pi > *x && *x > 0) {
                    cout << pi << "," << *x << "," << ti << endl;
                    shift = *x;
                    break;
                }
            }
            ti += shift;
            pi = P.length() - 1;
        }
        if (pi == -1) {
            pi = P.length() - 1;
            R.push_back(ti);
            if (info[T[ti]].size() <= 1) {
                ti += P.size();
            } else {
                ti += info[T[ti]][info[T[ti]].size() - 2];
            }
        }
    }
    return R;
}

int main () {
    string p;
    cin >> p;
    string t;
    cin >> t;
    auto R = BoyerMoorExtendBadCharMatch(t, p);
    for (auto x = R.begin(); x != R.end(); x++) {
        cout << *x << ",";
    }
    cout << endl;
}
