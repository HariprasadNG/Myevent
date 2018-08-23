#include <iostream>
#include <vector>

using namespace std;

void print(vector<char> &p) {
    for (auto x: p) {
        cout << x ;
    }
    cout << endl;
}

void generatePar(unsigned int pos, unsigned int o, unsigned int c, vector<char> &r) {
    if (c == r.size()/2) {
       print(r);
    } else {
        if (o > c) {
            r[pos] = '\\';
            generatePar(pos + 1, o, c+1, r);
        }
        
        if (o < r.size()/2) {
            r[pos] = '/';
            generatePar(pos + 1, o+1, c, r);
        }
    }
    return;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        unsigned int l;
        cin >> l;
        vector<char> r(2*l);
        generatePar(0, 0, 0, r);
    }
}
