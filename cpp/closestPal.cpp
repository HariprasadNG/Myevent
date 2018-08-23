#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Assumes s1 > s2 && s1.length() == s2.length()
int diff (string s1, string s2) {
    vector<int> s(s1.length(), 0);

    int xd = s1.length() - s2.length();
    for (int i = s2.length() - 1; i >= 0;i--) {
        int j = i-1 + xd;
        if (s1[i + xd] < s2[i]) {
            while (j>=0 && s1[j] == '0') {
                s1[j] = '9';
                j--;
            }
            s1[j] = s1[j] - 1;
            s[i+xd] = (10 + (int)s1[i+xd]) - (int)s2[i] + 1;
        } else {
            s[i+xd] = (int)s1[i+xd] - (int)s2[i];
        }
    }

    for (int i = 0; i < (s1.length() - s2.length()); i++) {
        s[i] = s1[i] - '0';
    }

    int m = 1;
    int d = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
        d += m * s[i];
        m *= 10;
    }
    return d;
}

string closest_pal(string s) {
    int i = 0;
    int j = s.length() - 1;
    while (i <= j) {
        if (s[i] != s[j]) {
            s[j] = s[i];
        }
        i++;
        j--;
    }
    return s;
}

string nearest_pal(string s) {
    int x = s.length()/2 - !(s.length() % 2);
    string x_1 = s;
    while (x >= 0 && x_1[x] == '0') {
        x_1[x] = '9';
        x--;
    }
    x_1[x] = x_1[x] - 1;
    if (x_1[0] == '0') {
        x_1 = x_1.substr(1, x_1.length() - 1);
    }
    string r_1 = closest_pal(x_1);
     
    x = s.length()/2 - !(s.length() % 2);
    string x1 = s;
    while (x >= 0 && x1[x] == '9') {
        x1[x] = '0';
        x--;
    }
    if ( x == -1) {
        x1 = "1" + x1;
    } else {
        x1[x] = x1[x] + 1;
    }
    string r1 = closest_pal(x1);

    x = s.length()/2 - !(s.length() % 2);
    string r = closest_pal(s);

    int d_1 = diff(s, r_1);
    bool g = false;
    for (int i = 0; i < s.length(); i++) {
        if ( s[i] < r[i]) {
            g = true;
            break;
        }
    }
    int d = g?diff(r,s):diff(s, r);
    int d1 = diff(r1, s);
    if (d_1 < d || d == 0) {
        return (d_1 <= d1) ? r_1:r1;
    }
    return (d <= d1) ? r: r1;

}

int main () {
    int T;
    cin >> T;
    while(T--) {
        string q;
        cin >> q;  
        if (q.length() == 1 && q[0] == '0'){
            cout << -1 << endl;
        } else if (q[0] == '-') {
            cout << -1 << endl;
        } else {
            cout << nearest_pal(q);
        }
    }
}
