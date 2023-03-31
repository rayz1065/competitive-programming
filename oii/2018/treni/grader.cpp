#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "treni.cpp"

int tempo_massimo(int, int[], int[]);

int main()
{
    int n;
    FILE *in = stdin, *out = stdout;
    assert(fscanf(in, "%d", &n) == 1);

    int *a = (int*)calloc(n, sizeof(int));
    int *b = (int*)calloc(n, sizeof(int));

    for(int i=0; i<n; i++){
      assert(fscanf(in, "%d", a + i) == 1);
      assert(fscanf(in, "%d", b + i) == 1);
    }

    int answ = tempo_massimo(n, a, b);
    fprintf(out, "%d\n", answ);

    free(a);
    free(b);

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}
