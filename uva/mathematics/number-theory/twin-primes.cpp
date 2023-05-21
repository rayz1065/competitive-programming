#include <bits/stdc++.h>
#define MAXP 20000010
#define MAXN 100010
using namespace std;

typedef unsigned long long int ll;

int sieveSize;
vector<int> primi;
bitset<MAXP> isP;

void eratostene(int ub){
    sieveSize = ub + 1;
    isP.set();
    isP[0] = isP[1] = false;

    for(int i = 2; i < sieveSize; i++){
        if(isP[i]){
            primi.push_back(i);
            for(ll j = (ll)i*i; j < sieveSize; j+= i)
                isP[j] = false;
        }
    }
}

pair<int, int> primePairs[MAXN];

int main(){
    eratostene(MAXP);

    int nPrimePairs = 0;
    for(int i = 0; i < primi.size() && nPrimePairs < MAXN; i++){
        int p = primi[i];
        if(isP[p + 2])
            primePairs[nPrimePairs++] = {p, p + 2};
    }

    int N;
    while(cin >> N){
        printf("(%d, %d)\n", primePairs[N - 1].first, primePairs[N - 1].second);
    }
}
