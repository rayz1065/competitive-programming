#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
char str[MAXN];
int kmp_jump[MAXN];

char str_rev(int i){
    return str[(2*n - i - 1)%n];
}

int len(char *str){
    int i = 0;
    while(str[i] != '\0') i++;
    return i;
}

void kmp(){
    int j = -1, i = 0;
    kmp_jump[0] = -1;

    while(i < n){
        while(j >= 0 && str[i] != str[j])
            j = kmp_jump[j];
        i++, j++;
        kmp_jump[i] = j;
    }
}

bool kmp_search(){
    int i = 0, j = 1;
    while(j < 2*n - 1){
        while(i >= 0 && str[i] != str_rev(j))
            i = kmp_jump[i];
        i++, j++;
        if(i == n) return true;
    }
    return false;
}

void init(){
    cin >> str;
    n = len(str);
    kmp();
}

bool is_palindrome(){
    for(int i = 0; i < n; i++)
        if(str[i] != str_rev(i))
            return false;
    return true;
}

//fstream out;

void solve(){
    if(kmp_search())
        cout<<"alindrome\n";
    else if(is_palindrome())
        cout<<"palindrome\n";
    else
        cout<<"simple\n";
}

int main(){
    //out.open("output.txt", ios::out);
    int T;
    cin >> T;

    while(T--)
        init(), solve();
}
