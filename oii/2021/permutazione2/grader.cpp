#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define maxn 1010

static FILE *in, *out;
static int N, A, B, C;
static int grader_pos = 0;
static int status = 1;
int query_cnt_a = 0;
static int query_cnt_b = 0;
static int query_cnt_c = 0;
static int F[maxn], P[maxn], H[maxn], i;

void indovina(int N, int A, int B, int C, int H[]);

bool chiedi(int K) {
#ifdef DEBUG
    printf("Queried for %d\n", K);
#endif
    query_cnt_a++;
    if (query_cnt_a > A) {
        fprintf(out, "Too many queries of type A"); exit(0);
    }
    if (K < 0 || K > N - 1) {
        fprintf(out, "Domanda non valida"); exit(0);
    }
    return (F[K] <= grader_pos);
}

void stato() {
    query_cnt_b++;
    status *= -1;
    if (query_cnt_b > B) {
        fprintf(out, "Too many queries of type B"); exit(0);
    }
#ifdef DEBUG
    printf("Changed state to %d\n", status);
#endif
}

void sposta() {
    query_cnt_c++;
    if (query_cnt_c > C) {
        fprintf(out, "Too many queries of type C"); exit(0);
    }
    grader_pos += status;
    if (grader_pos < 0 || grader_pos > N - 1) {
        fprintf(out, "Posizione non valida"); exit(0);
    }
#ifdef DEBUG
    printf("Changed pos to %d\n", grader_pos);
#endif
}

int main() {
    in = stdin;
    out = stdout;

    assert(fscanf(in, "%d", &N) == 1);
    assert(fscanf(in, "%d", &A) == 1);
    assert(fscanf(in, "%d", &B) == 1);
    assert(fscanf(in, "%d", &C) == 1);

    for (i = 0; i < N; i++) {
        assert(fscanf(in, "%d", &P[i]) == 1);
    }

    for (i = 0; i < N; i++) H[i] = 0;

    for (i = 0; i < N; i++) F[P[i]] = i;

    indovina(N, A, B, C, H);

    int flag = 1;
    for (i = 0; i < N; i++) {
        if (P[i] != H[i]) flag = 0;
    }

    for (i = 0; i < N; i++) {
        fprintf(out, "%d ", H[i]);
    }
    fprintf(out, "\n");

    if (flag == 1) {
        fprintf(out, "Risposta corretta: (%d, %d, %d) chiamate eseguite", query_cnt_a, query_cnt_b, query_cnt_c);
    } else {
        fprintf(out, "Risposta errata: (%d, %d, %d) chiamate eseguite", query_cnt_a, query_cnt_b, query_cnt_c);
    }

    return 0;
}
