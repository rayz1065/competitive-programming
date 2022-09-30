#include <bits/stdc++.h>
#ifdef _WIN32
#define getchar_unlocked() getchar()
#endif // _WIN32

using namespace std;

int N;

void fast_in(int &a){
    char c = getchar_unlocked();
    a = 0;
    while(c < '0')
        c = getchar_unlocked();
    while(c >= '0'){
        a = (a<<3) + (a<<1) + c - '0';
        c = getchar_unlocked();
    }
}

int main(){
    fast_in(N);
    int s = 0, o = 0, curr;

    for(int i = 0; i < N; i++){
        fast_in(curr);
        if(curr - o > s) s = curr - o;
        o = curr;
    }

    cout<<s<<"\n";
}
