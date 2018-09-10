#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>
#include<numeric>

using namespace std;
typedef unsigned int uint;

void print_spiral_help(vector<vector<int>> m, int off) {
    for (int i = off; i < m.size() - 1 - off; i++) {
        cout << m[off][i] << " ";
    }
    for (int i = off; i < m.size() - 1 - off; i++) {
        cout << m[i][m.size() - 1 - off] << " ";
    }
    for (int i = m.size() - 1 - off; i >= off + 1; i--) {
        cout << m[m.size() - 1 - off][i] << " ";
    }
    for (int i = m.size() - 1 - off; i >= off + 1; i--) {
        cout << m[i][off] << " ";
    }
}

void print_spiral (vector<vector<int>> m) {
    for ( int i = 0; i < m.size() / 2; i++) {
        print_spiral_help(m, i);
    }
    if ( m.size() % 2) {
        cout << m[m.size()/2][m.size()/2];
    }
}

int main () {
    vector<vector<int>> m1 = {
                                {0, 1, 2},
                                {3, 4, 5},
                                {6, 7, 8}
                            };
    vector<vector<int>> m2 = {
                                {0, 1},
                                {2, 3}
                             };

    vector<vector<int>> m3 = {
                                { 0,  1,  3,  4,  5},
                                { 6,  7,  8,  9, 10},
                                {11, 12, 13, 14, 15},
                                {16, 17, 18, 19, 20},
                                {21, 22, 23, 24, 25}

                             };
    vector<vector<int>> m4 = {
                                {0, 1, 3, 4},
                                {5, 6, 7, 8},
                                {9, 10, 11, 12},
                                {13, 14, 15, 16}
                             };
    print_spiral(m1);cout << endl;
    print_spiral(m2);cout << endl;
    print_spiral(m3);cout << endl;
    print_spiral(m4);cout << endl;
}
