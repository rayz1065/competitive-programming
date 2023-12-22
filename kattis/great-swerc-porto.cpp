#include <bits/stdc++.h>

#define MAXN 11
#define ALF 26

using namespace std;

int N;
char words[MAXN][MAXN];
int wordLen[MAXN];
int charCorr[ALF];
int charVal[10];

int getChVal(char c){
    return charVal[charCorr[c - 'A']];
}

int fact(int N){
    if(N <= 0)
        return 1;
    return fact(N - 1)*N;
}

int convWord(int i){
    int S = 0;
    for(int j = 0; j < wordLen[i]; j++)
        S = (S*10) + getChVal(words[i][j]);
    return S;
}

bool calc2(){
    int S = 0;
    for(int i = 0; i < N - 1; i++){
        S+= convWord(i);
    }

    return (S == convWord(N - 1));
}

int solve(){
    for(int i = 0; i < 10; i++)
        charVal[i] = i;
    for(int i = 0; i < ALF; i++)
        charCorr[i] = -1;

    int diffChars = 0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < MAXN && words[i][j] != '\0'; j++){
            wordLen[i] = j + 1;
            if(charCorr[words[i][j] - 'A'] == -1)
                charCorr[words[i][j] - 'A'] = diffChars++;
        }
    }

    int S = 0;
    do{
        bool valid = true;
        for(int i = 0; i < N; i++){
            if(getChVal(words[i][0]) == 0)
                valid = false;
        }
        if(valid){
            if(calc2()){
                S++;
            }
        }
    }
    while(next_permutation(charVal, charVal + 10));
    return S/fact(10 - diffChars);
}

bool init(){
    cin >> N;

    for(int i = 0; i < N; i++)
        cin >> words[i];

    return true;
}

int main(){
    init();
    printf("%d\n", solve());
}
