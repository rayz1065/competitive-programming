#include <bits/stdc++.h>
#define MAXN 105
#define MAXM 100005

using namespace std;

int n;
bool isPrime[MAXM];
vector<int> primi;

void init(){
    cin >> n;
}

void eratostene(){
    fill(isPrime + 2, isPrime + MAXM, true);
    for(int i = 2; i < MAXM; i++){
        if(isPrime[i]){
            primi.push_back(i);
            for(int j = i*2; j < MAXM; j+= i)
                isPrime[j] = false;
        }
    }
}

int findNum(){
    for(int i = 0; i + n - 1 < MAXM; i++){
        if(!isPrime[i] && isPrime[i + n - 1]){
            return i;
        }
    }
    assert(false);
}

void solve(){
    int num = findNum();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j)
                cout<<num<<" ";
            else
                cout<<1<<" ";
        }
        cout<<"\n";
    }
}

int main(){
    eratostene();
    int t;
    cin >> t;

    while(t--){
        init();
        solve();
    }
}
