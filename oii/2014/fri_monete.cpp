#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int N;
pair<int, int> velo[MAXN];
int divisibili[MAXN];
int lastVel[MAXN];
int maxS;

inline void cl(int a, int v){
    if(a == 1)
        return ;
    if(lastVel[a] != v)
        lastVel[a] = v, divisibili[a] = 0;
    maxS = max(maxS, ++divisibili[a]);
}

int monete(int N, int v[]) {
    for(int i = 0; i < N; i++){
        velo[i] = {v[i], i + 1};
    }

    sort(velo, velo + N);
    maxS = 0;
    for(int i = 0; i < N; i++){
        int sqr = sqrt(velo[i].second);
        cl(velo[i].second, velo[i].first);
        if(sqr*sqr == velo[i].second)
            cl(sqr, velo[i].first);
        for(int j = 2; j <= sqr; j++){
            if(velo[i].second%j == 0 && j != velo[i].second/j){
                cl(velo[i].second/j, velo[i].first);
                cl(j, velo[i].first);
            }
        }
    }
    return maxS;
}

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MAXN 100000

static int v[MAXN];

int main() {
	FILE* in = stdin;
	FILE* out = stdout;

	assert( 1 == fscanf(in, "%d", &N) );

	int i;
	for (i = 0; i < N; i++)
		assert( 1 == fscanf(in, "%d", &v[i]) );

	fprintf(out, "%d\n", monete(N, v));

	fclose(in);
	fclose(out);

	return EXIT_SUCCESS;
}
