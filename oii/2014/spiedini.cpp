#include <stdio.h>
#include <assert.h>
#define MAXN 20000000

static int N, K, i;
static int s[MAXN];


int solve(int N, int K, int* S) {
    int sum = 0;
    int frag = 0, iA = 0, iB = N - 1;
    while(iA < N && sum <= K){
        sum+= S[iA];
        if(S[iA] == 0)
            frag++;
        iA++;
    }
    iA--;
    while(iA >= 0 && S[iA] != 0)
        sum-= S[iA], iA--;

    int fragMax = frag;

    for(iB = N - 1; iB >= 0 && sum <= K; iB--){
        sum+= S[iB];
        if(iB <= iA)
            return fragMax;
        if(S[iB] == 0)
            frag++;
        if(frag > fragMax)
            fragMax = frag;

        while(iA >= 0 && (sum > K || S[iA] != 0)){
            if(S[iA] == 0)
                frag--;
            sum-= S[iA], iA--;
        }
    }
    return fragMax;
}

static FILE *fin, *fout;

int main(){
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    assert(2 == fscanf(fin, "%d%d", &N, &K));
    for(i=0; i<N; i++) assert(1 == fscanf(fin, "%d", &s[i]));
    fprintf(fout, "%d\n", solve(N, K, s));
    fclose(fin);
    fclose(fout);
    return 0;
}
