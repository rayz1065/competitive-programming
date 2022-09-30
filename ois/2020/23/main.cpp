#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstring>
#pragma GCC optimize ("O3")

#define DIVS 20
#define MAXL 50
#define MAXN 100000005
using namespace std;

char base_2[MAXL];
char base_3[MAXL];

void fill_base(char *str, int N, int base){
    if(N == 0){
        str[0] = '0';
        str[1] = '\0';
        return ;
    }
    int exp = 0;
    while(N > 0){
        str[exp] = N % base + '0';
        N/= base;
        exp++;
        str[exp] = '\0';
    }

    reverse(str, str + strlen(str));
}

int sum_digits(char *str){
    int l = strlen(str), s = 0;
    for(int i = 0; i < l; i++)
        s+= str[i] - '0';
    return s;
}

void add_pow(char *str, int base, int *sum_dig){
    int i = 0;
    while(true){
        if(str[i] == '\0')
            str[i] = '0', str[i + 1] = '\0';
        str[i]++;
        *sum_dig+= 1;
        if(str[i] - '0' < base)
            return ;
        str[i] = '0', *sum_dig-= base, i++;
    }
}

bool is_special(int N){
    fill_base(base_2, N, 2);
    fill_base(base_3, N, 3);

    int b3d = sum_digits(base_3), b2d = sum_digits(base_2);

    return b3d == b2d;
}

int memo[MAXN/DIVS];

int solve(int N){
    int s = memo[N/DIVS];
    for(int i = N - N%DIVS + 1; i <= N; i++){
        s+= is_special(i);
    }
    return s;
}

#ifdef _WIN32
    #define getchar_unlocked() getchar()
#endif // _WIN32

void readint(int &n){
    n = 0;
    char c = getchar_unlocked();
    while(c < '0') c = getchar_unlocked();
    while(c >= '0') n = n * 10 + c - '0', c = getchar_unlocked();
}

int main(){
    memo[0] = 0;
    base_2[0] = base_3[0] = '\0';
    int base_2_dig = 0, base_3_dig = 0;

    int s = 0;
    for(int i = 1; i < MAXN; i++){
        add_pow(base_2, 2, &base_2_dig);
        add_pow(base_3, 3, &base_3_dig);
        s+= (base_2_dig == base_3_dig);
        if(i%DIVS == 0)
            memo[i/DIVS] = s;
    }
    int T;
    readint(T);

    for(int i = 0; i < T; i++){
        int N;
        readint(N);
        cout<<solve(N)<<" ";
    }
}
