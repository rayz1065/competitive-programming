#include <assert.h>
#include <stdio.h>

#include <iostream>
#define MAXN 5000
#define MAXV 200000

using namespace std;
int memo[MAXN][MAXN];

int contentezza(int n, int* pizza){
    int mid;
    for(int a = n; a >= 0; a--)
        for(int b = a + (n%2 == 0); b < n; b+= 2){
            if(a == b) memo[a][b] = pizza[a];
            else{
                mid = memo[a + 1][b - 1];
                memo[a][b] = max(min(mid, memo[a + 2][b]) + pizza[a], min(memo[a][b - 2], mid) + pizza[b]);
            }
        }
    return memo[0][n - 1];
}

static int N;
static int V[MAXN];

int main(void)
{
  FILE* in = fopen("input.txt", "r");
  FILE* out = fopen("output.txt", "w");
  fscanf(in, "%d", &N);
  assert(1 <= N && N <= MAXN);

  int i;

  for(i=0; i<N; i++) {
  	fscanf(in, "%d", &V[i]);
    assert(1 <= V[i] && V[i] <= MAXV);
  }
  fprintf(out, "%d\n", contentezza(N, V));
  return 0;
}
