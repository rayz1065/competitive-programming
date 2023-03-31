#include <stdio.h>
#include <assert.h>
#define MAXN 100000
#define MAXM 100000
#include <bits/stdc++.h>

using namespace std;
void solve(int N, int Q, int *briganti, int *A, int *B, int *start, int *end, int *sol){}

int main()
{
    printf("ok");
    FILE *in, *out;
    assert(in = fopen("input.txt","r"));
    assert(out = fopen("output.txt","w"));

    int N , Q ;
    int pesi[MAXN] ;
    int a[MAXN] , b[MAXN] ;
    int qA[MAXM], qB[MAXM] ;
    int sol[MAXM] ;

    assert(2 == fscanf(in, "%d %d",&N,&Q));
    int i;
    for( i = 0 ; i < N ; i++ ) assert(1 == fscanf(in, "%d",pesi+i));
    for( i = 0 ; i < N-1 ; i++ ) assert(2 == fscanf(in, "%d %d",a+i,b+i));
    for( i = 0 ; i < Q ; i++ ) assert(2 == fscanf(in, "%d %d",qA+i,qB+i));
    solve(N,Q,pesi,a,b,qA,qB,sol);
    for( i = 0 ; i < Q ; i++ ) fprintf(out, "%d\n",sol[i]);

    return 0;
}
