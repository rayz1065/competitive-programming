#include <bits/stdc++.h>
#define MAXN 500001
using namespace std;

bool found[MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin>>N;
    int old = 0, curr;
    long long S = 0;
    for(int i = 0; i < N; i++){
        cin>>curr;
        if(curr < old){
            S+= old - curr;
            curr = old;
        }
        old = curr;
    }
    cout<<S;
}
