#include <iostream>
#include <string>
#include <stack>
#include <map>
#include <string.h>
using namespace std;

string postfix (string &ex) {
    string final = "";
    stack<char> ops;
    stack<char> vars;
    for (auto c: ex) {
        if ( c == '+' || c == '-') {
            ops.push(c);
        } else if ( c == '(') {
            ops.push('(');
        } else if ( c == ')') {
            while (!ops.empty()) {
                char x = ops.top();
                ops.pop();
                if ( x == '(') break;
                else {
                    final += x;
                }
            }
        } else if (c == ' ' ) {

        } else {
            final += c;
        }
    }
    while (!ops.empty()) {
        final += ops.top();
        ops.pop();
    }
    return final;
}

string combineSign(string s) {
    bool f = true;
    for (auto c: s) {
        if ( c == '-') {
            f = !f;
        }
    }
    if (f) return "+";
    else return "-";
}


#define ISALPHA(x) (x >= 'a' && x <= 'z') ||( x >= 'A' && x <= 'Z')
string eval(string x, string prefix, unsigned int &s) {
    string res = "";
    string sign = "";
    for (;s < x.length(); s++) {
        if ( ISALPHA(x[s])) {
            res = res + combineSign(prefix + sign) + x[s];
        } else if (x[s] == '+' || x[s] == '-') {
            sign = x[s];
        } else if (x[s] == '('){
            s++;
            res = res + eval (x , combineSign(prefix+sign), s);
        } else if (x[s] == ')') {
            return res;
        }
    }
    cout << res << endl;
    return res;
}

bool cmp (string s1, string s2) {
    int c1[26];
    int c2[26];
    memset((void*)c1, 0, sizeof(c1));
    memset((void*)c2, 0, sizeof(c2));
    for (unsigned int i = 0 ; i < s1.length(); i+=2) {
        bool inc = true;
        if (s1[i] != '+') {
            inc = false;
        }
        if (inc) {
            c1[s1[i+1] - 'a']++;
        } else {
            c1[s1[i+1] - 'a']--;
        }

    }

    for (unsigned int i = 0; i < s2.length(); i+=2) {
        bool inc = true;
        if (s2[i] != '+') {
            inc = false;
        }
        if (inc) {
            c2[s2[i+1] - 'a']++;
        } else {
            c2[s2[i+1] - 'a']--;
        }
    }

    for (unsigned int i = 0; i < 26; i++) {
        cout << i << ":" << c1[i] << ":" << c2[i] << endl;
        if (c1[i] != c2[i]) return false;
    }
    return true;
}

int main () {
    int T;
    cin >> T;
    while(T--) {
        string e1, e2;
        cin >> e1 >> e2;
        unsigned int i1 = 0;
        unsigned int i2 = 0;
        if (cmp(eval(e1, "", i1), eval(e2, "", i2))) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
}
