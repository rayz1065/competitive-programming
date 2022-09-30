#include <bits/stdc++.h>
#ifdef _WIN32
    #define getchar_unlocked getchar
#endif // _WIN32
#define MAXN 1000001

int N;
long long X[MAXN], Y[MAXN];

using namespace std;

int fastIn(){
    int S = 0;
    char c;
    c = getchar_unlocked();
    while(c >= '0'){
        S = S*10 + c - '0';
        c = getchar_unlocked();
    }
    return S;
}

int main() {
    N = fastIn();
    for(int i = 0; i < N; i++){
        X[i] = fastIn();
        Y[i] = fastIn();
    }

    long long area = 0;

    X[N] = X[0], Y[N] = Y[0];

    for(int i = 0; i < N; i++){
        area+= X[i]*Y[i + 1] - Y[i]*X[i + 1];
    }
    if(area < 0)
        area = -area;

    cout<<area/2;
    return 0;
}
