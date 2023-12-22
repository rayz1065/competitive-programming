#include <bits/stdc++.h>
#define MAXN 105

using namespace std;

int n;
int w[MAXN];
int wcount[MAXN << 1];
int maxw;

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> w[i];
    memset(wcount, 0, sizeof wcount);
}

int findPairsFor(int i, int s){
    int j = s - i;
    if(j <= 0) return 0;
    if(j == i) return wcount[i] - wcount[i]%2;
    return min(wcount[i], wcount[j]);
}

int findBestWithWeight(int s){
    int i = max(1, s - maxw);
    if(i > maxw)
        return 0;

    int dpairs = 0;
    while(i <= maxw){
        dpairs+= findPairsFor(i, s);
        i++;
    }
    assert(!(dpairs%2));
    return dpairs >> 1;
}

int solve(){
    for(int i = 0; i < n; i++)
        wcount[w[i]]++;

    maxw = *max_element(w, w + n);


    int best = 0;

    for(int s = 2; s <= maxw*2 + 5; s++){
        best = max(best, findBestWithWeight(s));
    }

    return best;
}

int main(){
    int t;
    cin >> t;

    while(t--){
        init();
        cout<<solve()<<"\n";
    }
}
