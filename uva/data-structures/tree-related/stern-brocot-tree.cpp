#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct rat_num{
    ll numer;
    ll denom;

    void print(){
        cout<<numer<<"/"<<denom<<"\n";
    }
};

rat_num mediant(rat_num a, rat_num b){
    return {a.numer + b.numer, a.denom + b.denom};
}

rat_num solve(string ops){
    rat_num lft = {0, 1}, curr = {1, 1}, rgt = {1, 0};

    for(int i = 0; i < ops.length(); i++){
        if(ops[i] == 'L'){
            rat_num memo = curr;
            curr = mediant(lft, curr);
            rgt = memo;
        }
        else{
            rat_num memo = curr;
            curr = mediant(curr, rgt);
            lft = memo;
        }
    }
    return curr;
}

int main(){
    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        string ops;
        cin >> ops;
        solve(ops).print();
    }
}
