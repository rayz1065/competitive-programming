#include <bits/stdc++.h>

using namespace std;

int N, M, S;

void init(){
    S = 0;
    cin >> M >> N;
}

int main(){
    FILE *out;
    out = stdout;
    while(true){
        init();
        if(N == 0 && M == 0)
            return 0;
        if(N == 0 || M == 0)
            S = 0;
        else if(N == 1 || M == 1)
            S = max(N, M);
        else if(N == 2 || M == 2){
            int m = max(N, M);
            int mod = m%4;
            if(mod > 2)
                mod = 2;
            S = max(m, (m - m%4) + mod*2);
        }
        else
            S = (N*M + 1)/2;
        //solve(0, 0, 0);
        fprintf(out, "%d knights may be placed on a %d row %d column board.\n", S, M, N);
    }
}
