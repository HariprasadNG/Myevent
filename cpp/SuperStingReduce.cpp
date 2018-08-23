#include<iostream>
#include<string>
using namespace std;

int main () {
    string s;
    cin >> s;
    char r[s.length()];
    int x = 0;
    for (auto c: s) {
        if (x == 0) {
            r[x++] = c;
        } else {
            if (r[x - 1] == c) {
                x--;
            } else {
                r[x++] = c;
            }
        }
    }
    if ( x == 0) {
        cout << "Empty String" << endl;
    } else {
        r[x] = '\0';
        cout << r;
    }
    return 0;
}
