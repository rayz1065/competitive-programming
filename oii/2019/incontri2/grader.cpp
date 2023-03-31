#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static FILE *in, *out;
static int N, *A, i;

bool visita(int N, int A[]);

int main() {
  in = stdin;
  out = stdout;

  assert(fscanf(in, "%d", &N) == 1);
  A = (int*)malloc(N * sizeof(int));
  for (i = 0; i < N; i++) {
    assert(fscanf(in, "%d", A + i) == 1);
  }

  if (visita(N, A)) {
    fprintf(out, "Emil\n");
  } else {
    fprintf(out, "Gemma\n");
  }

  return 0;
}
