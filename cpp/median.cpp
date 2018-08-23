#include <iostream>
#include <vector>
#include <map>
#include <utility>
#error hi
using namespace std;

int median (vector<vector<int>> &mat) {
    map<int, pair<int,int>> m;
    for (int i = 0; i < mat.size(); i++) {
        m.emplace(make_pair(mat[i][0], make_pair(i,0)));
    } 
    int minR = m.begin()->second.first; 
    int minC = m.begin()->second.second; 
    int mid = ((mat.size() * mat[0].size()) >> 1);
    for (int i = 0; i < mid ; i++) {
        minR = m.begin()->second.first; 
        minC = m.begin()->second.second;
        m.erase(m.begin());
        minC++;
        if (minC < mat[0].size()) 
            m.emplace(make_pair(mat[minR][minC], make_pair(minR, minC)));
    }
    return m.begin()->first;
}

int main () {
    int T;
    cin >> T;
    while(T--) {
        int r, c;
        cin >> r >> c;
        vector<vector<int>> mat;
        int ir = 0;
        while (ir < r) {
            mat.push_back(vector<int>());
            int ic = 0;
            while ( ic < c) {
                int temp;
                cin >> temp;
                mat[ir].push_back(temp);
                ic++;
            }
            ir++;
        }
        cout << median(mat) << endl;
    }
}
