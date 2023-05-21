#include <iostream>
#include <cstring>
#include <fstream>
#define MAXN 105
#define MAXK 105

using namespace std;

int n, k;
char str[MAXK],
     str_nxt[MAXK];

int len(char *str){
    int i = 0;
    while(str[i] != '\0') i++;
    return i;
}

void init(){
    cin >> k >> n;
    cin >> str;
}

bool is_match(char *str, char *str2){
    int i = 0;
    while(i < MAXK && str[i] != '\0' && str[i] == str2[i])
        i++;

    return str[i] == '\0';
}

int count_diff(char *str1, char *str2){
    for(int i = 0; i < k; i++)
        if(is_match(str1 + i, str2))
            return i;
    return k;
}

int solve(){
    int s = k;

    for(int i = 1; i < n; i++){
        cin >> str_nxt;
        s+= count_diff(str, str_nxt);

        strcpy(str, str_nxt);
    }

    return s;
}

//#define cout out

int main(){
    //fstream out;
    //out.open("output.txt", ios::out);

    int T;
    cin >> T;

    while(T--)
        init(), cout<<solve()<<"\n";
}
