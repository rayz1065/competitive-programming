#include <bits/stdc++.h>
#define MAXN 10005
using namespace std;

int domande[MAXN];

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    int N, K;
    in >> N >> K;
    for(int i = 0; i < N; i++)
        in >> domande[i];
    sort(domande, domande + N);

    int minS = domande[K - 1] - domande[0];
    for(int i = 0; i + K - 1 < N; i++){
        minS = min(minS, domande[i + K - 1] - domande[i]);
    }
    out<<minS;
}
