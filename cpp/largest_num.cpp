#include <iostream>
#include <vector>
#include <string>
using namespace std;

void largest(string &num) {
    int lastIndex = num.length();
    for (int i = num.length() - 1; i > 0; i--) {
        if (num[i] < num[i-1]) {
            lastIndex = i - 1;
        }
    }
    cout << lastIndex << endl;
    if (lastIndex < num.length()) {
        char c = num[lastIndex] - 1;
        num[lastIndex] = c;
        for (int i = lastIndex + 1; i < num.length(); i++) {
            num[i] = '9';
        }
    }
}

void trimZero(string &num) {
    int i = 0;
    for (;i < num.length(); i++) {
        if (num[i] != '0') break;
    }
    num = num.substr(i, num.length());
}

int main () {
    int T;
    cin >> T;
    while(T--) {
        string s;
        cin >> s;
        trimZero(s);
        largest(s);
        cout << s << endl;
    }
}
