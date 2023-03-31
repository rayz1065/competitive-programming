#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "catene.cpp"

long long profitto_massimo(int N, int U[], int V[], int W[]);

int main(){
    int n;
    FILE *in = stdin, *out = stdout;
    assert(fscanf(in, "%d", &n) == 1);

    int *u = (int*)calloc(n-1, sizeof(int));
    int *v = (int*)calloc(n-1, sizeof(int));
    int *w = (int*)calloc(n-1, sizeof(int));

    for(int i=0; i<n-1; i++)
      assert(fscanf(in, "%d%d%d", u + i, v + i, w + i) == 3);

    long long answ = profitto_massimo(n, u, v, w);
    fprintf(out, "%lld\n", answ);

    free(u);
    free(v);
    free(w);

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}
