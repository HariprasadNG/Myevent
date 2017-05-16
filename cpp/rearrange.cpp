#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

int main () {
    int T;
    cin >> T;
    while(T--) {
        vector<unsigned int> ct(26);
        string s;
        cin >> s;
        bool p = true;
        for (auto c: s) {
            ct[c - 'a']++;
            if (ct[c - 'a'] > (s.length() + s.length()%2)/2) {
                p = false;
                break;
            }
        }
        cout << p << endl;
     
    }
}
