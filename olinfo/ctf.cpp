#include <bits/stdc++.h>
#ifdef _WIN32
    #define getchar_unlocked getchar
    #define putchar_unlocked putchar
#endif // _WIN32
using namespace std;

inline unsigned long long int fastIn(){
    char c;
    unsigned long long int N = 0;
    c = getchar_unlocked();
    while(c >= '0'){
        N = (N<<3) + (N<<1) + c - '0';
        c = getchar_unlocked();
    }
    return N;
}

inline void fastOut(unsigned long long int N){
    unsigned long long int memo = 0;
    int l = 0;
    while(N > 0){
        memo = memo*10 + N%10;
        N/= 10;
        l++;
    }
    //return;
    while(l > 0){
        putchar_unlocked(memo%10 + '0');
        memo/= 10;
        l--;
    }

}

int main(){
    int t;
    unsigned long long int N;
    t = fastIn();
    for(int i = 0; i < t; i++){
        N = fastIn();

        N-= (unsigned long long int)1<<(63 - __builtin_clzll(N));

        fastOut((N<<1) + 1);
        putchar_unlocked('\n');
    }
}

