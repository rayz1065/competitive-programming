#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "yutaka.cpp"
int taglia(int, int[]);

int main()
{
    int n;
    FILE *in = stdin, *out = stdout;
    assert(fscanf(in, "%d", &n) == 1);

    int *v = (int*)calloc(n, sizeof(int));

    for(int i=0; i<n; i++)
      assert(fscanf(in, "%d", v + i) == 1);

    int answ = taglia(n, v);
    fprintf(out, "%d\n", answ);

    free(v);

    fclose(in);
    fclose(out);

    return EXIT_SUCCESS;
}
