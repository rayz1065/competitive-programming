#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

int n;
char num[MAXN];

void init(){
    cin >> n;
    cin >> num;
}

int solve(){
    // raze: start, odd pos, odd num
    // breach: second, even pos, even num

    if(n == 1)
        return 2 - num[0]%2;
    if(n%2){
        for(int i = 0; i < n; i+= 2){
            if((num[i] - '0')%2)
                return 1;
        }
        return 2;
    }
    else{
        for(int i = 1; i < n; i+= 2){
            if((num[i] - '0')%2 == 0)
                return 2;
        }
        return 1;
    }
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
