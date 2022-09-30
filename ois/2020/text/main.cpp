#include <bits/stdc++.h>
#define MAXN 100005
#define MAXK 1000000005

using namespace std;

int n, k;

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    cin >> n >> k;

    int curr = 0;

    for(int i = 0; i < n; i++){
        string a;
        cin >> a;

        int l = a.length();

        if(curr + l + (curr > 0) > k)
            cout<<"\n", curr = 0;
        if(curr == 0){
            cout<<a;
            curr+= l;
        }
        else{
            cout<<" "<<a;
            curr+= l + 1;
        }
    }
}
