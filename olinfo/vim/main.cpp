#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;

inline int fastMod(int num, int N){
    return ((num < N)?num:num-N);
}

void valuta(int N, int C[], int L[], int P[]){
    for(int i = 0; i < N; i++){
        C[i] = C[i] - L[i];
        P[i] = false;
    }
    int i = 0;
    while(i < N){
        if(C[i] >= 0 && C[fastMod(i + N - 1, N)] <= 0){
            int benzina = 0, j = i;
            while(benzina >= 0 && j < i + N)
                benzina+= C[fastMod(j, N)], j++;
            if(benzina < 0)
                i = j;
            else{
                int benzina = 0, j = i;
                while(j <= i + N){
                    if(benzina == 0)
                        P[fastMod(j, N)] = true;
                    benzina+= C[fastMod(j, N)], j++;
                }
                return;
            }
        }
        else
            i++;
    }
	return ;
}
