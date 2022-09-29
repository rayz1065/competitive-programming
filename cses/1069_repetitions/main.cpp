#include <bits/stdc++.h>
#define MAXN 500001
using namespace std;

bool found[MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string gattaca;
    cin>>gattaca;

    int curr = 1, best = 1;
    for(unsigned int i = 1; i < gattaca.size(); i++){
        if(gattaca[i] == gattaca[i - 1]){
            if(++curr > best)
                best = curr;
        }
        else
            curr = 1;
    }
    cout<<best;
}
