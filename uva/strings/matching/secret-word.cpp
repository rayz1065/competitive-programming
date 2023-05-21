#include <bits/stdc++.h>
#define MAXN 1000005

using namespace std;

char str[MAXN], str_rev[MAXN];
int n;
int kmp_jump[MAXN];

void kmp_init(){
    kmp_jump[0] = -1;
    int i = 0, j = -1;

    while(i < n){
        while(j >= 0 && str[i] != str[j])
            j = kmp_jump[j];
        i++, j++;
        kmp_jump[i] = j;
    }
}

int kmp_count(){
    int s = 0;
    int i = 0, j = 0;
    while(i < n && j < n){
        while(j >= 0 && str[j] != str_rev[i])
            j = kmp_jump[j];
        i++, j++;
        s = max(s, j);
    }
    assert(i == n);
    return s;
}

void init(){
    cin >> str;
    n = strlen(str);

    strcpy(str_rev, str);
    reverse(str_rev, str_rev + n);

    kmp_init();
}

//fstream out;
//#define cout out

void solve(){
    int j = kmp_count();
    //cout<<str<<(str_rev + j)<<"\n";
    cout<<(str_rev + n - j)<<"\n";
}

int main(){
    //out.open("output.txt", ios::out);

    int t;
    cin >> t;
    while(t--)
        init(), solve();
}
