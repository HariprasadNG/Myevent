#include<iostream>
#include<string.h>
using namespace std;

int mat[50][50];

void recursiveFill(int r, int c, int s, int e, int rd, int cd) {
    if (mat[s][e] <= 1) return;
    if (cd != 0 && e+cd < c && e+cd >= 0) {
        if (mat[s][e+cd] == 1) {
            mat[s][e+cd] = mat[s][e];
            recursiveFill(r,c,s,e+cd,0,cd);
            recursiveFill(r,c,s,e+cd,1,cd);
            recursiveFill(r,c,s,e+cd,-1,cd);
        }
    }

    if ( rd != 0 && s+rd < r && s+rd >= 0) {
        if (mat[s+rd][e] == 1) {
            mat[s+rd][e] = mat[s][e];
            recursiveFill(r,c,s+rd,e,rd,0);
            recursiveFill(r,c,s+rd,e,rd,1);
            recursiveFill(r,c,s+rd,e,rd,-1);
        }
    }
}

void printMat (int r, int c) {
    for(int i = 0; i < r; i++) {
        for(int j = 0; j < c; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

int countShapes(int r, int c) {
    int x = 2;
    for (int i = 0; i < r; i++) {
        for (int j = 0 ; j < c; j++){
            if (mat[i][j] == 1) {
                //New Shape
                mat[i][j] = x++;
                recursiveFill(r,c,i,j,0,1);
                recursiveFill(r,c,i,j,0,-1);
                recursiveFill(r,c,i,j,1,0);
                recursiveFill(r,c,i,j,-1,0);
            }
        }
    }

    return x - 2;
}

void readInput(int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            char c;
            cin >> c;
            if (c == 'O') {
                mat[i][j] = 0;
            } else if (c == 'X') {
                mat[i][j] = 1;
            } else {
                j--;
            }
        }
    }
}

int main () {
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int r,c;
        cin >> r;
        cin >> c;
        readInput(r, c);
        cout << countShapes(r,c) << endl;
        //printMat(r,c);
        //cout << endl;
    }
}
