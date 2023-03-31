#include <stdio.h>
#pragma GCC optimize("O3")
FILE *f;

int fastin() {
    int v = 0;
    char minus = 0;
    char c = fgetc(f);
    if (c == '-') {
        minus = 1;
        c = fgetc(f);
    }
    while (c >= '0') {
        v = v * 10 + c - '0';
        c = fgetc(f);
    }
    return v * (1 - minus * 2);
}

long long somma(FILE *_f) {
    f = _f;
    int n;
    long long int s = 0;
    fscanf(f, "%d", &n);
    fgetc(f);
    while (n--) {
        int v = fastin();
        s+= v;
    }
    return s;
}
