#include<iostream>
#include<set>
#include<string>


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

int main () {
    Braces(4);    
}
