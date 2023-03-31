#include <cstdio>
#include <cassert>
#include <cstdlib>

static FILE *fr, *fw;

// Declaring variables
static int N;
static int Q;
static int T;
static int* A;
static int* B;
static int* C;
static int* U;
static int* V;
static long long int* res;

// Declaring functions
void inizia(int N, int T, int A[], int B[], int C[]);
long long int distanza1(int u, int v);
long long int distanza2(int u, int v);
long long int minimo(int u, int v);
long long int massimo(int u, int v);
void run(int Q, int T, int U[], int V[], long long int res[]);

// Functions ad-hoc for this grader
void run(int Q, int T, int U[], int V[], long long res[]) {
  for (int i = 0; i < Q; i++) {
    if (T == 0)
      res[i] = distanza1(U[i], V[i]);
    else if (T == 1)
      res[i] = distanza2(U[i], V[i]);
    else if (T == 2)
      res[i] = minimo(U[i], V[i]);
    else if (T == 3)
      res[i] = massimo(U[i], V[i]);
    else
      assert(!"Invalid value for T");
  }
}

int main() {
    fr = stdin;
    fw = stdout;

	// Reading input
	fscanf(fr, " %d %d %d", &N, &Q, &T);
	A = (int*)malloc((N-1) * sizeof(int));
	B = (int*)malloc((N-1) * sizeof(int));
	C = (int*)malloc((N-1) * sizeof(int));
	for (int i0 = 0; i0 < N-1; i0++) {
		fscanf(fr, " %d %d %d", &A[i0], &B[i0], &C[i0]);
	}
	U = (int*)malloc((Q) * sizeof(int));
	V = (int*)malloc((Q) * sizeof(int));
	for (int i0 = 0; i0 < Q; i0++) {
		fscanf(fr, " %d %d", &U[i0], &V[i0]);
	}

	// Calling functions
	inizia(N, T, A, B, C);
	res = (long long int*)malloc((Q) * sizeof(long long int));
	run(Q, T, U, V, res);

	// Writing output
	for (int i0 = 0; i0 < Q; i0++) {
		fprintf(fw, "%lld ", res[i0]);
	}
	fprintf(fw, "\n");

    fclose(fr);
    fclose(fw);
    return 0;
}
