#include <bits/stdc++.h>
#define MAXN 1000005
#define getchar getchar
using namespace std;

int monumenti[MAXN*2];

inline int read_int(){
    char c = getchar(); int v = 0;
    while(c < '0' || c > '9') c = getchar();
    while(c >= '0' && c <= '9'){v = (v << 1) + (v << 3) + int(c - '0'); c = getchar();}
    return v;
}

int main(){
    int N, K, L, h = 0;
    cin >> N >> K >> L;
    for(int i = 0; i < N; i++){
        int position = read_int();
        monumenti[i] = position;
    }
    sort(monumenti, monumenti + N);
    for(int i = 0; i < N; i++)
        monumenti[i + N] = monumenti[i] + 2*K;
    int minS;

    if(L == 1){
        int S = 0;
        int a = 0, b = 0, a2 = h, b2 = h, i = 0; // monumenti da a => b e da a2 => b2
        while(b < 2*N && monumenti[b] < i + L)
            b++;
        while(b2 < 2*N && monumenti[b2] < i + K + L)
            b2++;
        minS = b - a + b2 - a2;
        for(int m = 0; m < N && i <= K; m++){
            i = monumenti[m] + 1;
            while(monumenti[a] < i)
                a++;
            while(monumenti[a2] < i + K)
                a2++;
            while(monumenti[b] < i + L)
                b++;
            while(monumenti[b2] < i + L + K)
                b2++;
            minS = min(b - a + b2 - a2, minS);
        }
    }
    else{
        int S = 0;
        int a = 0, b = 0, a2 = 0, b2 = 0, i = 0; // monumenti da a => b e da a2 => b2
        minS = INT_MAX;

        for(int m = -1; m < N && monumenti[m] + 1 <= K; m++){
            if(m != -1)
                i = monumenti[m] + 1;
            while(monumenti[a] < i)
                a++;
            while(monumenti[a2] < i + K)
                a2++;
            while(monumenti[b] < i + L)
                b++;
            while(monumenti[b2] < i + L + K)
                b2++;
            minS = min(b - a + b2 - a2, minS);
        }
    }

    cout<<minS;
}
