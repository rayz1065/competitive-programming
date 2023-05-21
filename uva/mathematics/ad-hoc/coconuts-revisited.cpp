#include<bits/stdc++.h>

using namespace std;

bool solve(int remP, int remC, int totP){
    if(remP == 0){
        return (remC%(totP) == 0);
    }
    if(remC%totP != 1)
        return false;
    return solve(remP - 1, remC - 1 - remC/totP, totP);
}

int main(){
    FILE *out = stdout;

    int N;
    while(cin >> N){
        if(N < 0)
            break ;

        bool solved = false;
        for(int p = sqrt(N) + 1; !solved && p > 0; p--){
            if(solve(p, N, p)){
                fprintf(out, "%d coconuts, %d people and %d monkey\n", N, p, 1);
                solved = true;
            }
        }
        if(!solved)
            fprintf(out, "%d coconuts, no solution\n", N);
    }
}
