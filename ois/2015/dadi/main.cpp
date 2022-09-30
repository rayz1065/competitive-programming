#include <bits/stdc++.h>

#define MAXN 100000
using namespace std;

enum{FRONT, TOP, RIGHT, BACK, BOTTOM, LEFT};

void simula(int N, char C[], int R[]) {
    int cubo[6];
    int cuboMemo[6];
    cubo[FRONT] = 2, cubo[BACK] = 5;
    cubo[TOP] = 1, cubo[BOTTOM] = 6;
    cubo[RIGHT] = 3, cubo[LEFT] = 4;

    int op = 0;
    for(int i = 0; i < N; i++){
        if(C[i] == 'F')
            R[op++] = cubo[FRONT];
        else if(C[i] == 'T')
            R[op++] = cubo[TOP];
        else if(C[i] == 'R')
            R[op++] = cubo[RIGHT];
        else{
            for(int i = 0; i < 6; i++)
                cuboMemo[i] = cubo[i];
            if(C[i] == 'X'){
                cubo[FRONT] = cuboMemo[TOP];
                cubo[BOTTOM] = cuboMemo[FRONT];
                cubo[BACK] = cuboMemo[BOTTOM];
                cubo[TOP] = cuboMemo[BACK];
            }
            if(C[i] == 'Y'){
                cubo[TOP] = cuboMemo[RIGHT];
                cubo[LEFT] = cuboMemo[TOP];
                cubo[BOTTOM] = cuboMemo[LEFT];
                cubo[RIGHT] = cuboMemo[BOTTOM];
            }
            if(C[i] == 'Z'){
                cubo[RIGHT] = cuboMemo[FRONT];
                cubo[BACK] = cuboMemo[RIGHT];
                cubo[LEFT] = cuboMemo[BACK];
                cubo[FRONT] = cuboMemo[LEFT];
            }
        }
    }
}

char C[MAXN];
int R[MAXN];

int main() {
    FILE *fr, *fw;
    int N, M, i;

    fr = fopen("input.txt", "r");
#ifdef EVAL
    fw = fopen("output.txt", "w");
#else
    fw = stdout;
#endif
    assert(1 == fscanf(fr, "%d\n", &N));
    M = 0;
    for (i = 0; i < N; ++i) {
        assert(1 == fscanf(fr, "%c", &C[i]));
        if (C[i] == 'T' || C[i] == 'F' || C[i] == 'R')
            ++M;
    }

    simula(N, C, R);
    for (i = 0; i < M; ++i)
        fprintf(fw, "%d ", R[i]);
    fprintf(fw, "\n");

    fclose(fr);
    fclose(fw);
    return 0;
}
