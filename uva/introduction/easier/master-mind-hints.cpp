#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

int N;
int soluzione[MAXN];
int tent[MAXN];

void init(){
    cin >> N;
    for(int i = 0; i < N; i++)
        cin >> soluzione[i];
}

bool inputTent(){
    for(int i = 0; i < N; i++)
        cin >> tent[i];
    return (tent[0] != 0);
}

pair<int, int> compara(int A[], int B[]){
    pair<int, int> S = {0, 0};
    bool usedA[N] = {}, usedB[N] = {};

    for(int i = 0; i < N; i++){
        if(A[i] == B[i])
            S.first++, usedA[i] = usedB[i] = true;
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; !usedA[i] && j < N; j++){
            if(!usedB[j] && A[i] == B[j])
                S.second++, usedA[i] = usedB[j] = true;
        }
    }
    return S;
}

int main(){
    FILE *out = stdout;

    for(int t = 1;; t++){
        init();
        if(N == 0)
            return 0;
        fprintf(out, "Game %d:\n", t);

        while(inputTent()){
            auto S = compara(soluzione, tent);
            fprintf(out, "    (%d,%d)\n", S.first, S.second);
        }
    }
}
