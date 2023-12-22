#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

int n;

int sph[MAXN];
int sol[MAXN];

void init(){
    /*n = 10;
    for(int i = 0; i < n; i++)
        sph[i] = i + 1;
    return ;*/
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> sph[i];
}

int calcCheap(){
    int s = 0;
    for(int i = 1; i < n - 1; i++)
        if(sol[i - 1] > sol[i] && sol[i + 1] > sol[i])
            s++;
    return s;
}

int solve(){
    sort(sph, sph + n);

    int ch = (n)/2;

    for(int i = 0; i < n; i++){
        if(i%2){
            sol[i] = sph[i/2];
        }
        else{
            sol[i] = sph[i/2 + ch];
        }
        // cout<<i<<" -> "<<i%2<<" -> "<<i/2 + ch<<"\n";
    }

    return calcCheap();
}

int brute_force_sol(){
    sort(sph, sph + n);
    for(int i = 0; i < n; i++)
        sol[i] = sph[i];

    int bestSol = 0;

    do{
        bestSol = max(bestSol, calcCheap());
    } while(next_permutation(sol, sol + n));

    return bestSol;
}

void genSph(int i, int lst){
    if(i == n){
        for(int i = 0; i < n; i++)
            cout<<sph[i]<<" ";
        cout<<"\n";

        assert(brute_force_sol() == solve());
        return ;
    }

    sph[i] = lst;
    genSph(i + 1, lst);

    if(i == 0)
        return ;

    lst++;
    sph[i] = lst;
    genSph(i + 1, lst);
}

int main(){
    init();
    //genSph(0, 1);
    //return 0;
    //assert(brute_force_sol() == solve());
    cout<<solve()<<"\n";
    for(int i = 0; i < n; i++)
        cout<<sol[i]<<" ";
    cout<<"\n";
}
