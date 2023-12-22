#include <bits/stdc++.h>

using namespace std;

int n;

vector<int> remElement(vector<int> curr, int idx){
    int n = curr.size();
    int a = (idx - 1 + n)%n, b = (idx + 1)%n;
    if(a > b)
        swap(a, b);

    curr[idx] = curr[a] + curr[b];
    curr.erase(curr.begin() + b);
    curr.erase(curr.begin() + a);
    return curr;
}

int solve(vector<int> curr){
    if(curr.size() == 1)
        return curr[0];

    int n = curr.size(), s = 0;
    for(int i = 0; i < n; i++){
        vector<int> tmp = remElement(curr, i);
        int s2 = solve(tmp);
        s = max(s, s2);
    }
    return s;
}

int main(){
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];

    cout<<solve(a)<<"\n";;
}
