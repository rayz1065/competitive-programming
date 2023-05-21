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

bool isPrime(ll x){
    if(x < sieveSize)
        return isP[x];
    for(int i = 0; i < primi.size() && (ll)primi[i]*primi[i] <= x; i++){
        if(x%primi[i] == 0)
            return false;
    }
    return true;
}

int findFirstPrime(int m, int t){
    for(ll i = m; i <= t; i++)
        if(isPrime(i))
            return i;
    return -1;
}

int main(){
    FILE *out = fopen("output.txt", "w");
    eratostene(MAXP - 1);

    int L, U;
    while(cin >> L >> U){
        int a = findFirstPrime(L, U);
        if(a == -1){
            fprintf(out, "There are no adjacent primes.\n");
            continue ;
        }
        int b = findFirstPrime(a + 1, U);
        if(b == -1){
            fprintf(out, "There are no adjacent primes.\n");
            continue ;
        }

        int minDist = INT_MAX >> 1, maxDist = -1, aMinDist, bMinDist, aMaxDist, bMaxDist;

        while(b != -1){
            if(b - a < minDist)
                minDist = b - a, aMinDist = a, bMinDist = b;
            if(b - a > maxDist)
                maxDist = b - a, aMaxDist = a, bMaxDist = b;
            a = b;
            b = findFirstPrime(b + 1, U);
        }
        fprintf(out, "%d,%d are closest, %d,%d are most distant.\n", aMinDist, bMinDist, aMaxDist, bMaxDist);
    }
}
