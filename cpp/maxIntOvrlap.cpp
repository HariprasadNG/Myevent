#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxGuest(vector<int> &in, vector<int> &out) {
    int max = 0;
    sort(in.begin(), in.end());
    sort(out.begin(), out.end());
    int time = in[0];
    int inside = 0;
    unsigned int j = 0;
    for (unsigned int i = 0 ; i < in.size(); i++) {
        while (j < out.size() && in[i] > out[j] ) {
            inside--;
            j++;
        }
        inside++;
        if (max < inside)  {
            max = inside;
            time = in[i];
        }
    }
    cout << max << " " << time << endl;
    return max;
}


int main () {
    int T;
    cin >> T;
    while(T--) {
        int g = 0;
        cin >> g;
        vector<int> in;
        vector<int> out;
        for (int i = 0; i < g; i++) {
            int temp;
            cin >> temp;
            in.push_back(temp);
        }
        for (int i = 0; i < g; i++) {
            int temp;
            cin >> temp;
            out.push_back(temp);
        }
        maxGuest(in, out);
    }
}
