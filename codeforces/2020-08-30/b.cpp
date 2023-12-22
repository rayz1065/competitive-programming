#include <bits/stdc++.h>
#define MAXN 100005
#define VERY_LARGE (lli) MAXN*INT_MAX
using namespace std;

typedef long long int lli;

int n;
lli num[MAXN];

void init(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> num[i];
}

double logbasen(int b, lli x) {
    return (log(x)/log(b));
}

lli calcSol(int c){
    lli ctti = 1, s = 0;
    if(n > logbasen(c, VERY_LARGE))
        return VERY_LARGE;
    for(int i = 0; i < n; i++, ctti*= c)
        s+= llabs(num[i] - ctti);

    return s;
}

lli solve(){
    lli bestSol = VERY_LARGE;
    sort(num, num + n);

    //for(int c = 10000; c < 100000; c++)
    //    cout<<c<<": "<<logbasen(c, VERY_LARGE)<<" "<<pow(c, logbasen(c, VERY_LARGE))<<"\n";

    lli lastSol = 0;
    lli currMin = 1, currMax = 1000000000;

    while(currMax - currMin > 5){
        lli currMid = (currMin + currMax) >> 1;
        lli currSol = calcSol(currMid);
        if(currSol >= VERY_LARGE){
            currMax = currMid;
        }
        else if(calcSol(currMid - 1) < currSol){
            currMax = currMid;
        }
        else{
            currMin = currMid;
        }
    }
    for(lli c = currMin; c <= currMax; c++){
        bestSol = min(bestSol, calcSol(c));
    }

    return bestSol;
}

int main(){
    init();
    cout<<solve()<<"\n";
}
