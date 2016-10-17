#include <iostream>
#include <vector>
using namespace std;

int main () {
    vector<int> c1 = {1,2,13,40,50};
    vector<int> c2 = {5,6,7,13,14,15,16,41,42,50};
    int c1i = 0, c2i = 0;
    int nonCrooks = 0;
    while (c1i < c1.size() && c2i < c2.size()) {
        if (c1[c1i] < c2[c2i]) {
            c1i++;
            nonCrooks++;
        } else if (c1[c1i] == c2[c2i]) {
            c1i++;
            c2i++;
        } else {
            c2i++;
            nonCrooks++;
        }
    }
    nonCrooks += (c1.size() - c1i) + (c2.size() - c2i);
    cout << "Non crooks " << nonCrooks << endl;
}
