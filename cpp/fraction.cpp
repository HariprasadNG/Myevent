#include <iostream>
#include <vector>
#include <string>
using namespace std;

string Fraction(int u, int d, vector<int>& res) {
    string result = (res.size() > 0) ? ".":"";
    if (u == 0) {
        for (auto y: res) {
            result += to_string(y/d);;
        }
        return result;
    } else {
        for (auto x: res) {
            if (x == u) {
               for (auto y: res) {
                if (y == u) result += '(';
                result += to_string(y/d);
               }
               result += ')';
               return result;
            }
        }
    }
    res.push_back(u);
    u = (u % d) * 10;
    return Fraction(u, d, res);
}

int main () {
    int T;
    cin >> T;
    while(T--) {
        int u;
        int d;
        cin >> u >> d;
        string res;
        res += to_string(u/d);
        u = (u % d)*10;
        vector<int> frac;
        res += Fraction(u, d, frac);
        cout << res << endl;
    }
}
