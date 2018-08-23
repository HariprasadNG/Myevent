#include<iostream>
#include<vector>
#include<map>
#include <string>

using namespace std;
/// This hufman coding is not right......
//average bit lenght is 2.39 with this method but you can 2.24 for the given example
//See hufMan_correct.cpp for the right solution
vector<pair<char, string> > encode(map<int,char>::iterator s, 
                                   map<int,char>::iterator e, 
                                   string suffix = "") {
    int total = 0;
    int count = 0;

    //This loop can be avoided by passing
    //the value computed from the below 
    //loop as the input parameter for the function
    for(auto x = s; x != e; x++) {
        total += x->first;
        count++;
    }
    
    if(count < 1) return vector<pair<char,string> >();
    if(count == 1) {
        vector<pair<char, string> > r = {{s->second, suffix}};
        return r;
    }

    int temp = 0;
    auto it = s;
    for(; it != e && total/2 > temp; it++) {
        temp += it->first;
    }

    auto left = encode(s, it,  suffix + "0");
    auto right = encode(it, e,  suffix + "1");
    left.insert(left.end(),right.begin(), right.end());
    return left;
}

int main () {
    multimap<int, char, greater<int>> Mapping;
    Mapping.emplace(5,'A');
    Mapping.emplace(9,'B');
    Mapping.emplace(12,'C');
    Mapping.emplace(13,'D');
    Mapping.emplace(16,'E');
    Mapping.emplace(45,'F');

    auto r = encode(Mapping.begin(),  Mapping.end(), "");

    for( auto x: r) {
        cout << x.first << ":" << x.second << endl;
    }
}
