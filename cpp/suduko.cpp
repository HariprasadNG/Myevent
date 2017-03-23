#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

int Mat[9][9];

bool isValidMove(int x, int y, int v) {
    //Check ro
    for(int i = 0; i < 9; i++) {
        if( (i != y) && Mat[x][i] == v) return false;
        if( (i != x) && Mat[i][y] == v) return false;
    }

    int sr = (x/3) * 3;
    int sc = (y/3) * 3;
    for(int i = 0; i < 3; i++) {
        for (int j = 0; j <3; j++) {
            if(((sr+i) != x) && ( (sc+j) != y) && Mat[sr+i][sc+j] == v) {
                return false;
            }
        }
    }

    return true;
}
bool StartBackTracking (int r, int c) {
    for (int i = r; i < 9; i++) {
        for (int j = c; j < 9; j++) {
            if (Mat[i][j] == 0) {
               for (int x = 1; x <= 9; x++) {
                    Mat[i][j] = x;
                    if (isValidMove(i, j, x)) {
                        if(StartBackTracking(i, j+1)) {
                            return true;
                        }
                    }
                    Mat[i][j] = 0;
               }
               return false;
            }
        }
        c = 0;
    }
    return true;
}
int main() {
    int t;
    cin >> t;
    for (int ii = 0; ii < t; ii++) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cin >> Mat[i][j];
            }
        }
        //Deduce(mat);
        StartBackTracking(0, 0);
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                cout << Mat[i][j] << " ";
            }
        }
        cout << endl;
    }
}
