#include<iostream>
#include<vector>
#include<stack>
#include <map>
#include <cmath>

using namespace std;

map<char, int> prio = {{'+', 0 }, {'-', 0}, {'*', 1 }, {'/', 1}, {'^', 2}};

int printMissing (vector<int> &a) {
    int i = 1;
    int m = 0;
    for (auto x: a) {
        m = (m^x)^i++;
    }
    m = m ^ (a.size() + 1);
    cout << "Missing Number \n";
    cout << m << endl;
    return m;
}

float operation (float o1, float o2, char op) {
    switch(op) {
        case '+':
            return o1 + o2;
        case '-':
            return o1 - o2;
        case '*':
            return o1 * o2;
        case '/':
            return o1 / o2;
        case '^':
            return pow(o1, o2);
    }
    return -1;
}
string evaluatePostFix(vector<string> pf) {
    stack<string> oprand;
    for (auto x:pf) {
        if (prio.find(x[0]) != prio.end()) {
            string so1 = oprand.top();
            float o1 = stof(so1);
            oprand.pop();
            string so2 = oprand.top();
            float o2 = stof(so2);
            oprand.pop();
            oprand.push(to_string(operation(o2, o1, x[0])));
        } else {
            oprand.push(x);
        }
    }
    return oprand.top();
}

vector<string> infixToPostFix(string exp) {
    vector<string> prefix;
    string tk = "";
    stack<char> op;
    for (auto x: exp) {
        if (x >= '0' && x <= '9') {
            tk += x;
        } else if (x == ' ') {
            if( tk != "")
                prefix.push_back(tk);
            tk = "";
        } else {
            //Operator
            if (tk != "")
                prefix.push_back(tk);
            tk = "";
            if (op.size() == 0) {
                op.push(x);
            } else {
                while (op.size() > 0 && prio[op.top()] > prio[x]) {
                    prefix.push_back(string("") + op.top());
                    op.pop();
                }
                op.push(x);
            }
        }
    }
    if (tk != "") prefix.push_back(tk);
    while (op.size() > 0) {
        prefix.push_back(string("") + op.top());
        op.pop();
    }
    return prefix;
}

#define SWAP(A, B)  {int x = A; A = B; B = x;}
int QsPart2(vector<int> &a) {
    int s = 0;
    int e = a.size() -1;
    int p = a[s++];
    int c = s;
    while (s <= e) {
        if (a[s] < p) {
            SWAP(a[s], a[c]);
            s++; c++;
        } else if (a[s] == p) {
            s++;
        } else {
            SWAP(a[e], a[s]);
            e--;
        }
    }
    if (c == 0) return 0;
    SWAP(a[0], a[c-1]);
    cout << "{" << c - 1 << ", " << s -1 << "}" << endl;
    return c-1;
}
//2 Way partation
int QsPart(vector<int> &a) {
    int s = 1;
    int e = a.size() -1;
    while ( s < e) {
        if (a[0] >= a[s]) {
            s++;
        } else {
            while (s <= e && a[e] > a[0]) {
                e--;
            }
            if (e > s) {
                int x= a[s];
                a[s] = a[e];
                a[e] = x;
                e--;
            }
            if (e < s) {
               break;
            }
        }
    }

    if (a[e] < a[0]) {
        int x = a[e];
        a[e] = a[0];
        a[0] = x;
    } else { 
        return 0;
    }
    return e;
}
void printV(vector<int> v) {
    for (auto x: v) {
        cout << x << " ";
    }
    cout << endl;
}
int main() {
	vector<int> a;
    for (int i = 1; i <= 10; i++) {
        a.push_back(i);
    }
    printMissing(a);
    a.erase(a.begin());
    printMissing(a);
    a.push_back(1);
    a.erase(a.begin() + 5);
    printMissing(a);

    string ex = "9*9+1+10^2";
    cin >> ex;
    auto postFix = infixToPostFix(ex);
    for (auto x : postFix) {
        cout << x << " ";
    }
    cout << endl;
    cout << evaluatePostFix(postFix);
    return 0;
	for(int i = 0; i < 10; i++ ) {
		a.push_back(i);
		//a.at(5);
	}
    //cout << QsPart2(a) << endl;
    //printV(a);
    //a = {5,4,3,2,1};
    //cout << QsPart(a) << endl;
    //printV(a);
    a = {3, 2, 1, 4, 5};
    cout << QsPart2(a) << endl;
    printV(a);

    a = {3, 2, 1, 4, 5, 3, 3};
    cout << QsPart2(a) << endl;
    printV(a);

    a = {1,1,1,1,4};
    cout << QsPart2(a) << endl;
    printV(a);

    a = {2, 1, 1, 1};
    cout << QsPart2(a) << endl;
    printV(a);
}
