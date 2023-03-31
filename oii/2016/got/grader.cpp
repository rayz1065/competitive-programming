#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static FILE *fin, *fout;
static int subtask, N, M, K, S, E, T;
static int *A, *B, *W, *P, *V;

int avoid_volunteers(int, int, int, int, int, int, int, int[], int[], int[], int[], int[]);

int main() {
    fin = stdin;
    fout = stdout;

    assert(fscanf(fin, "%d%d%d%d%d%d%d", &subtask, &N, &M, &K, &S, &E, &T) == 7);

    A = (int *)malloc(M * sizeof(int));
    B = (int *)malloc(M * sizeof(int));
    W = (int *)malloc(M * sizeof(int));
    P = (int *)malloc(M * sizeof(int));
    V = (int *)malloc(M * sizeof(int));

    for (int i = 0; i < M; i++)
        assert(fscanf(fin, "%d%d%d%d%d", A + i, B + i, W + i, P + i, V + i) == 5);

    fprintf(fout, "%d\n", avoid_volunteers(subtask, N, M, K, S, E, T, A, B, W, P, V));

    fclose(fin);
    fclose(fout);

    return EXIT_SUCCESS;
}
