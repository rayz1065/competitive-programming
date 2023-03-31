#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void prepara(int N);

int ribalta();

int main() {
    int N, N_fact;
    FILE *fin = stdin, *fout = stdout;

    assert(fscanf(fin, "%d", &N) == 1);

    N_fact = 1;
    for (int i = 2; i <= N; i++)
        N_fact *= i;

    int perm[N];
    for(int i=0; i<N; i++)
      perm[i] = i+1;

    for (int i = 0; i < N; i++)
        fprintf(fout, "%d ", perm[i]);
    fprintf(fout, "\n");

    prepara(N);
    for (int i = 0; i < N_fact; i++) {
        int res = ribalta();
        assert(res >= 1 && res <= N);
        for(int j=0; j<res/2; j++)
        {
          int tmp = perm[j];
          perm[j] = perm[res-j-1];
          perm[res-j-1] = tmp;
        }

        for (int i = 0; i < N; i++)
            fprintf(fout, "%d ", perm[i]);
        fprintf(fout, "\n");
    }

    fclose(fin);
    fclose(fout);

    return EXIT_SUCCESS;
}
