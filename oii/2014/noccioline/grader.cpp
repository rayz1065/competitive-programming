#include <stdio.h>
#include <assert.h>
#define MAXN 10005

static int secchi[MAXN];

static int N,K,i;

int ContaOperazioni(int N,int K, int* secchi);

int main(){
  FILE *in = stdin, *out = stdout;
  // assert(in = fopen("input.txt", "r"));
  // assert(out = fopen("output.txt", "w"));
  
  assert(1 == fscanf(in, "%d", &N));
  assert(1 == fscanf(in, "%d", &K));
  for( i = 0; i < N; ++i) assert(1 == fscanf(in, "%d", secchi+i));
  fprintf(out, "%d\n", ContaOperazioni(N,K,secchi));
  return 0;
}
