#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_N 50000
#define MAX_M 10000000

static int N, M;
static int R[MAX_M][2];
static int L[MAX_M];
static int K;
static int P[MAX_N];
static int solution;

extern int travel_plan(int N, int M, int R[][2], int L[], int K, int P[]);

int main()
{
  int i;
  FILE *fr = fopen("input.txt", "r");
  assert(3==fscanf(fr, "%d %d %d",&N,&M,&K));
  for(i=0; i<M; i++)
    assert(3==fscanf(fr, "%d %d %d",&R[i][0],&R[i][1],&L[i]));
  for(i=0; i<K; i++)
    assert(1==fscanf(fr, "%d",&P[i]));
  fclose(fr);
  FILE *fw = fopen("output.txt", "w");
  fprintf(fw, "%d\n", travel_plan(N,M,R,L,K,P));
  fclose(fw);
  return 0;
}
