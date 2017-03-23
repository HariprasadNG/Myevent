#include<iostream>
#include<string>
using namespace std;

string ip;
void printMat(int *mat, int l) {
    for(int i = 0; i < l; i++) {
        for(int j = 0; j < l; j++) {
            cout << mat[i*l + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void TrueFalseBrases (){
    int tr[ip.length()][ip.length()];
    int fl[ip.length()][ip.length()];

    //Initial filling
    for(int i = 0; i < ip.length(); i++) {
        for(int j = 0; j < ip.length(); j++) {
            if (i == j) {
                tr[i][j] = (ip[i] == 'T')?1:0;
                fl[i][j] = (ip[i] == 'F')?1:0;
            } else {
                tr[i][j] = 0;
                fl[i][j] = 0;
            }
        }
    }

    for (int i = 2; i < ip.length(); i+=2) {
        for (int j = 0; j < ip.length()-i; j+=2) {
            for(int x = 2; x <= i; x+=2 ){
                if (ip[j+x-1] == '|') {
                    tr[j][j+i] = tr[j][j+i-x]*tr[j+i-x+2][j+i] + fl[j][j+i-x]*tr[j+i-x+2][j+i] + tr[j][j+i-x]*fl[j+i-x+2][j+i];
                    fl[j][j+i] = fl[j][j+i-x]*fl[j+i-x+2][j+i];
                } else if (ip[j+x-1] == '&') {
                    tr[j][j+i] = tr[j][j+i-x]*tr[j+i-x+2][j+i];
                    fl[j][j+i] = fl[j][j+i-x]*fl[j+i-x+2][j+i] + fl[j][j+i-x]*tr[j+i-x+2][j+i] + tr[j][j+i-x]*fl[j+i-x+2][j+i];
                } else if (ip[j+x-1] == '^') {
                    fl[j][j+i] = tr[j][j+i-x]*tr[j+i-x+2][j+i] + fl[j][j+i-x]*fl[j+i-x+2][j+i];
                    tr[j][j+i] = tr[j][j+i-x]*fl[j+i-x+2][j+i] + fl[j][j+i-x]*tr[j+i-x+2][j+i];
                }
            }
        }
    }

    printMat((int*)tr, ip.length());
    cout << "----------FALSE----------" << endl;
    printMat((int*)fl, ip.length());
}

int main () {
    int t = 0;
    cin >> t;
    for (int i = 0;i < t; i++) {
        cin >> ip;
        TrueFalseBrases();
    }
}
