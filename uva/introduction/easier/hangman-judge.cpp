#include <bits/stdc++.h>
#define ALF 26
#define MAXL 100000
#define LOSE 7
using namespace std;

bool tried[ALF];
bool parola[ALF];
char input[MAXL];
int t;

bool init(){
    cin >> t;
    if(t == -1)
        return false;

    fill(tried, tried + ALF, false);
    fill(parola, parola + ALF, false);

    cin >> input;
    for(int i = 0; i < MAXL && input[i] != '\0'; i++)
        parola[input[i] - 'a'] = true;
    return true;
}

int contaLettere(){
    int S = 0;
    for(int i = 0; i < ALF; i++)
        if(parola[i])
            S++;
    return S;
}

int simula(){
    cin >> input;
    int errori = 0, mancanti = contaLettere();
    for(int i = 0; i < MAXL && input[i] != '\0'; i++){
        if(!tried[input[i] - 'a']){
            tried[input[i] - 'a'] = true;
            if(parola[input[i] - 'a']){
                mancanti--;
                if(mancanti <= 0)
                    return 1;
            }
            else{
                errori++;
                if(errori >= LOSE)
                    return -1;
            }
        }
    }
    return 0;
}

int main(){
    FILE *out = stdout;

    while(true){
        if(!init())
            return 0;
        int r = simula();
        fprintf(out, "Round %d\n", t);
        if(r == 1)
            fprintf(out, "You win.\n");
        if(r == 0)
            fprintf(out, "You chickened out.\n");
        if(r == -1)
            fprintf(out, "You lose.\n");
    }
}
