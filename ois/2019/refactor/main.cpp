#include <bits/stdc++.h>
#define MAXN 5000005
#define MAXM 100005
using namespace std;

enum {NORMALE, COMMENTO, STRINGA, COMMENTO_MULTILINEA};

char testo[MAXN];
char needle[MAXM];

bool isCharacter(int i){
// has an underscore or a lowercase/uppercase letter as the first character;
// is only formed by digits, underscores, lowercase/uppercase letters;
// is not inside acommentor astring literal.
    return (testo[i] == '_' || (testo[i] >= 'a' && testo[i] <= 'z') || (testo[i] >= 'A' && testo[i] <= 'Z') || (testo[i] >= '0' && testo[i] <= '9'));
}

int main(){
    cin >> needle;

    int stato = NORMALE;

    int N = 0;
    while((testo[N] = getchar_unlocked()) != EOF){
        N++;
    }
    testo[N] = '\0';

    int S = 0;

    for(int i = 0; i < N; i++){
        if(stato == STRINGA){
            while(i < N && testo[i] != '"')
                i++;
            stato = NORMALE;
        }
        else if(stato == COMMENTO){
            while(i < N && testo[i] != '\n')
                i++;
            stato = NORMALE;
        }
        else if(stato == COMMENTO_MULTILINEA){
            while(i < N && !(testo[i] == '/' && testo[i - 1] == '*'))
                i++;
            stato = NORMALE;
        }
        else{
            if(testo[i] == '"')
                stato = STRINGA;
            else if(i > 0 && testo[i] == '*' && testo[i - 1] == '/')
                stato = COMMENTO_MULTILINEA;
            else if(i > 0 && testo[i] == '/' && testo[i - 1] == '/')
                stato = COMMENTO;
            else if(isCharacter(i)){
                int f = 0;
                while(i < N && needle[f] != '\0' && testo[i] == needle[f])
                    i++, f++;
                if(needle[f] == '\0' && !isCharacter(i))
                    S++;
                while(i < N && isCharacter(i))
                    i++;
            }
        }
    }
    
    cout<<S<<"\n";
}