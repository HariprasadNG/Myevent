#include<iostream>

using namespace std;

bool mat[10][10];

void Zero(int n) {
    for(int i = 0; i < n; i++) {
        for (int j = 0 ; j < n; j++) {
            mat[i][j] = false;
        }
    }
}

bool validPos(int n, int x, int y) {
    if ( x >= n || y >= n) return false;
    
    //Row
    for (int i = x-1; i >= 0; i--) {
        if (mat[i][y]) return false;
    }

    //Column
    for (int i = y-1; i >= 0; i--) {
        if (mat[x][i]) return false;
    }

    //Left down diagonal
    for (int i = x-1, j = y-1; 
             i >= 0 && j >= 0;
             i--, j--) {
        if(mat[i][j]) return false;
    }

    //Right down  diagonal
    for (int i = x-1, j = y+1;
             i >= 0 && j < n;
             i--, j++) {
        if(mat[i][j]) return false;
    }

    return true;
}

void printSoln (int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if(mat[i][j])cout << j + 1 << " ";
        }
    }
    cout << "]" << endl;
}

int findQueenInRow (int n, int r) {
    if ( r < 0 || r >= n) return -1;
    for (int i = 0; i < n; i++) {
        if(mat[r][i])return i;
    }
    return -1;
}

void enumSol(int n) {
    int i = 0;
    int j = 0;
    while (true) {
        for (;i < n; i++) {
            for (;j < n; j++) {
                if(validPos(n, i, j)) {
                    mat[i][j] = true;
                    j = 0;
                    break;
                }
            }
            if (j == n) {
              j = findQueenInRow(n, i-1);
              while (j == n-1 && i > 1) {
                mat[i-1][j] = false;
                i = i - 1;
                j = findQueenInRow(n, i - 1);
              }
              mat[i-1][j] = false;
              j = j + 1;
              i = i - 2;
              if (i < -1) return; //Done
            } else if (i == n-1) {
                //Valid solution try to 
                //Find one more solution
                //By chaning the position
                //of last valid move
                printSoln(n);
                j = findQueenInRow(n, i);
                while (j == n - 1 && i >= 1) {
                    mat[i][j] = false;
                    i = i - 1;
                    j = findQueenInRow(n , i);
                }
                mat[i][j] = false;
                i = i - 1;
                j = j + 1;
                if ( i < 0) return; //Done
            }
        }
    }
}

int main () {
    int t = 0;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n;
        cin >> n;
        Zero(n);
        enumSol(n);
        cout << endl;
    }
    return 0;
}
