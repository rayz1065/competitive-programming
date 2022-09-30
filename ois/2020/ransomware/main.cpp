#include <bits/stdc++.h>
#define MAXN 105
#define MAXL 1005
#define ENCLEN 105

using namespace std;

int n;
char numeri[MAXN][MAXL];
char encr[10][ENCLEN];
int encrlen[10];

int getnum(char *a, int &i){
    for(int j = 0; j < 10; j++){
        if(strncmp(a + i, encr[j], encrlen[j]) == 0){
            i+= encrlen[j];
            return j;
        }
    }
    i = MAXN;
    return -1;
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> numeri[i];
    for(int i = 0; i < 10; i++)
        cin >> encr[i], encrlen[i] = strlen(encr[i]);

    for(int a = 0; a < n; a++){
        int i = 0;
        while(i < MAXN && numeri[a][i] != '\0')
            cout<<getnum(numeri[a], i);
        cout<<"\n";
    }
}
