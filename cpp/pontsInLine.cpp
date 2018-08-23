#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main () {
    int n;
    cin >> n;
    multiset<int, greater<int>> s;
    while (n--) {
        int temp;
        cin >> temp;
        s.emplace(temp);
    }
    set<int> res;
    res.emplace(0);
    s.erase(s.find(0));
    while (!s.empty()) {
        res.emplace(*s.begin());
    }
}
