#include <bits/stdc++.h>
#define MAXN 100

using namespace std;

int n;
int nums[MAXN];

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> nums[i];
}

void solve(){
    int s = 0;
    for(int i = 0; i < n; i++)
        s+= nums[i];
    if(s == 0){
        cout<<"NO\n";
    }
    else{
        sort(nums, nums + n);
        if(s > 0)
            reverse(nums, nums + n);

        cout<<"YES\n";
        for(int i = 0; i < n; i++)
            cout<<nums[i]<<" ";
        cout<<"\n";
    }
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        solve();
    }
}
