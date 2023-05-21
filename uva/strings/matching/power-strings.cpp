#include <bits/stdc++.h>
#define MAXN 1000005

using namespace std;

int n;
char str[MAXN];
int kmp_jump[MAXN];

void init_kmp(){
    int i = 0, j = -1;
    kmp_jump[0] = -1;

    while(i < n){
        while(j >= 0 && str[i] != str[j])
            j = kmp_jump[j];
        i++, j++;
        kmp_jump[i] = j;
    }
}

bool init(){
    cin >> str;
    n = strlen(str);
    if(str[0] == '.' && n == 1)
        return false;

    init_kmp();
    return true;
}

int kmp(char *haystack, int m){
    int i = 0, j = 0;
    while(i < m && j < n){
        while(j >= 0 && haystack[i] != str[j])
            j = kmp_jump[j];
        i++, j++;
    }
    assert(i == m);

    int len = (n - j);
    if(n%len == 0)
        return n/len;
    return 1;
}

int solve(){
    return kmp(str + 1, n - 1);
    /*for(int i = 0; i < n; i++)
        cout<<i<<" ";
    cout<<"\n";
    for(int i = 0; i < n; i++)
        cout<<(char)((kmp_jump[i] != -1) ? kmp_jump[i] + '0' : '/')<<" ";
    cout<<"\n";
    for(int i = 0; i < n; i++)
        cout<<str[i]<<" ";
    cout<<"\n\n";*/
    /*int jump = (n - 1) - kmp_jump[n - 1];
    for(int i = jump; i < n; i++)
        if(i - kmp_jump[i] != jump) return 1;
    return n/jump;*/
}

//#define cout out
int main(){
    //fstream out;
    //out.open("output.txt", ios::out);
    while(init())
        cout<<solve()<<"\n";
}
