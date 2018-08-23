#include<iostream>
using namespace std;
int sp(int l) {
    if (l == 0) return 1;
    if (l == 1) return 1;
    int x = 1;
    for (int i = 2; i <= l; i++) {
        int y = i * sp(l - i);
        x = (x > y)?x:y;
    }
    return x;
}

int main () {
    int x;
    cin >> x;
    cout << sp(x);
}
