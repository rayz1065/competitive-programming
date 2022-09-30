#include <iostream>
#include <algorithm>
#ifdef _WIN32
    #define getchar_unlocked() getchar()
#endif // _WIN32

#pragma GCC optimize ("O3")

#define MAXN 50005
#define MAXV 50005

using namespace std;

int n, v;
int eventi[MAXN], vouch[MAXV];

void readint(int &n){
    n = 0;
    char c = getchar_unlocked();
    while(c < '0') c = getchar_unlocked();
    while(c >= '0') n = n * 10 + c - '0', c = getchar_unlocked();
}

int main(){
    readint(n), readint(v);
    for(int i = 0; i < n; i++)
        readint(eventi[i]);
    for(int i = 0; i < v; i++)
        readint(vouch[i]);

    sort(eventi, eventi + n);
    sort(vouch, vouch + v);

    int i = 0, j = 0;
    while(i < n && j < v){
        if(eventi[i] <= vouch[j])
            i++;
        j++;
    }

    cout<<i<<"\n";
}
