#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
vector<int> initial_state;

/*bool is_dismutation(vector<int> &initial, vector<int> &curr, int n){
    for(int i = 0; i < n; i++)
        if(initial[i] == curr[i])
            return false;
    return true;
}

bool is_eq(vector<int> &initial, vector<int> &curr, int n){
    for(int i = 0; i < n; i++)
        if(initial[i] != curr[i])
            return false;
    return true;
}

bool next_dismutation(vector<int> &initial, vector<int> &curr, int n){
    while(next_permutation(curr.begin(), curr.end())){
        if(is_eq(initial, curr, n))
            return false;
        if(is_dismutation(initial, curr, n))
            return true;
    }
    if(is_eq(initial, curr, n))
        return false;
    if(is_dismutation(initial, curr, n))
        return true;
    return next_dismutation(initial, curr, n);
}

bool check_perm(vector<int> initial_state, int n){
    vector<int> a(initial_state);

    while(next_dismutation(initial_state, a, n)){
        if(is_useful(a, n)){
            return true;
        }
    }
    return false;
}*/

bool is_useful(vector<int> &curr, int n){
    for(int i = 0; i < n; i++)
        if(curr[i] == i + 1)
            return false;
    return true;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        cin >> n;
        initial_state.resize(n);

        for(int i = 0; i < n; i++)
            cin >> initial_state[i];

        /*while(next_permutation(initial_state.begin(), initial_state.end())){
            assert(check_perm(initial_state, n));
        }*/

        if(is_sorted(initial_state.begin(), initial_state.end()))
            cout<<0<<"\n";
        else if(is_useful(initial_state, n))
            cout<<1<<"\n";
        else
            cout<<2<<"\n";
    }
}
