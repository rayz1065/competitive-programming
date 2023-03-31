#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum {BLACK, RED, GREEN} color_t;

void find_secret(int, int);

static color_t *csolution;
static int N, T;
static int callcount = 0;

#define OUTPUT_AND_EXIT(ecode, args...)			\
  {							\
    FILE *fd  = fopen("output.txt", "w");		\
    if (fd != NULL) {					\
      fprintf(fd, args);				\
      fclose(fd);					\
    }							\
    free(csolution);					\
    exit(ecode);					\
  }							\

int examine(color_t combination[]) {
  int total = 0;

  for (int i = 0; i < N; i++) {
    if (combination[i] != RED && combination[i] != BLACK && combination[i] != GREEN) {
      OUTPUT_AND_EXIT(3, "%d COLOR_VIOLATION", i);
    }

    if (combination[i] == GREEN || csolution[i] == GREEN || csolution[i] == combination[i])
      total++;
  }
  callcount++;
  return total;
}

void solution(color_t combination[]) {
  int equal = 0;
  for (int i = 0; i < N; i++)
    if (combination[i] == csolution[i])
      equal++;

  if (equal == N) {
    OUTPUT_AND_EXIT(0, "%d CORRETTO", callcount);
  } else {
    OUTPUT_AND_EXIT(0, "%d SBAGLIATO", callcount);
  }
}

int main(int argc, char *argv[]) {
  if (1 != scanf(" %d", &N))
    OUTPUT_AND_EXIT(2, "-2 MALFORMED_INPUT");
  if (1 != scanf(" %d", &T))
    OUTPUT_AND_EXIT(2, "-1 MALFORMED_INPUT");

  csolution = (color_t*) malloc(N * sizeof(color_t));
  char color;

  for (int i = 0; i < N; i++) {
    assert(1 == scanf(" %c", &color));
    switch (color) {
    case 'B': csolution[i] = BLACK; break;
    case 'R': csolution[i] = RED; break;
    case 'G': csolution[i] = GREEN; break;
    default: OUTPUT_AND_EXIT(2, "%d MALFORMED_INPUT", i); break;
    }
  }

  find_secret(N, T);
  return EXIT_SUCCESS;
}

#undef OUTPUT_AND_EXIT
