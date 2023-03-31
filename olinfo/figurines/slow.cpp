// https://training.olinfo.it/#/task/figurines/statement
#include <bits/stdc++.h>
#define MAXD 100005

using namespace std;

int n;
int curr_day;
vector<int> states[MAXD];

void init(int n) {
    ::n = n;
}

void log(vector<int>& added, vector<int>& removed) {
    curr_day++;
    set<int> rem;
    for (auto i: removed) rem.insert(i);
    for (auto i: states[curr_day - 1]) {
        if (rem.find(i) == rem.end()) {
            states[curr_day].push_back(i);
        }
    }
    for (auto i: added) states[curr_day].push_back(i);
}

int answer(int d, int x) {
    int s = 0;
    for (auto i: states[d]) s += i >= x;
    return s;
}
