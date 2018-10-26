#include<iostream>
#include<set>
#include<string>
#include<vector>


using namespace std;
char buffer[1024];

void createFirstBrac(char* buf, int n) {
    for (int i = 0;i < n; i++) {
        buf[i] = '(';
        buf[i+n] = ')';
    }
}

void GenerateBraces (char *s, char *e) {
    int n = e - s + 1;
    cout << buffer << endl;
    if (n <= 2)return;
    s[1] = ')';
    for (int i = n - 2; i >= n/2; i--) {
        s[i] = '(';
        cout << buffer << endl;
        s[i] = ')';
    }
    createFirstBrac(s + 2, (n - 2) / 2);
    GenerateBraces(s + 2, e);
}
void Braces (int n) {
    createFirstBrac(buffer, n);
    buffer[n*2] = 0;
    GenerateBraces(buffer, buffer + n*2 - 1);
}

void BracesWorking (int n, string prefix = "", string suffix = "") {
    if (n == 0) {
        cout << prefix << suffix << endl;
        return;
    }
    if (n == 1) {
        cout << prefix << "{}" << suffix << endl;
        return;
    }
    if (n == 2) {
        cout << prefix << "{{}}" << suffix << endl;
        cout << prefix << "{}{}" << suffix << endl;
        return;
    }
    BracesWorking(n-1, prefix + "{", suffix + "}");
    BracesWorking(n-1, prefix + "{}", suffix);
    BracesWorking(n-2, prefix + "{", suffix + "}{}");
}


int cat (int n) {
    if ( n == 0) return 1;
    if ( n == 1) return 1;
    int count = 0;
    for (int i = 0; i <= n - 1; i++) {
        count += cat(i)*cat(n-1-i);
    }
    return count;
}

void catbc (int ob, int cb, string r) {
    if ( cb == 0 && ob == 0) {
        cout << r << endl;
    }

    if (ob > 0) {
        catbc(ob - 1, cb, r + "{");
    }
    if (cb > ob) {
        catbc(ob, cb - 1, r + "}");
    }
}


int main () {
    int c = 10;
    cin >> c;
    //cout << cat(c) << endl;;
    catbc(c, c, "");
    //Braces(c);    
}
