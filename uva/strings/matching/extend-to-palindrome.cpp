#include <bits/stdc++.h>
#define MAXN 100005

using namespace std;

char str[MAXN], str_rev[MAXN];
int n;
int kmp_jump[MAXN];

int len(char *str){
    int s = 0;
    while(str[s] != '\0') s++;
    return s;
}

void kmp_init(){
    kmp_jump[0] = -1;
    int i = 0, j = -1;

    while(i < n){
        while(j >= 0 && str_rev[i] != str_rev[j])
            j = kmp_jump[j];
        i++, j++;
        kmp_jump[i] = j;
    }
}

int kmp_count(){
    int i = 0, j = 0;
    while(i < n && j < n){
        while(j >= 0 && str_rev[j] != str[i])
            j = kmp_jump[j];
        i++, j++;
    }
    assert(i == n);
    return j;
}

bool init(){
    if(!(cin >> str))
        return false;
    n = len(str);
    if(n == 0) return false;

    strcpy(str_rev, str);
    reverse(str_rev, str_rev + n);

    kmp_init();
    return true;
}

//fstream out;
//#define cout out

void solve(){
    int j = kmp_count();
    cout<<str<<(str_rev + j)<<"\n";
}

int main(){
    //out.open("output.txt");
    while(init())
        solve();
}
