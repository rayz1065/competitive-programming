#include <bits/stdc++.h>
#define MAXN 50001
using namespace std;

void itera(string &S){
    int i = 0;
    while(i < S.size()){
        if(abs(S[i] - S[i + 1]) == 32){
            S.erase(i, 2);
            i = 0;
        }
        else
            i++;
    }
}

void rimuoviCarattere(string &S, char c){
    c = tolower(c);
    for(int i = 0; i < S.size(); i++){
        if(S[i] == c || S[i] == (char)(c - 32) || S[i] == (char)(c + 32)){
            S.erase(i--, 1);
        }
    }
}

int main(){
    fstream in, out;
    in.open("input5.txt", ios::in);

    string polimero;
    in>>polimero;
    string oldPolimero = polimero;

    itera(polimero);

    cout<<"Senza togliere lettere: "<<polimero.length()<<endl;

    int best = 0, bestVal = INT_MAX;
    for(int i = 0; i < 26; i++){
        polimero = oldPolimero;
        rimuoviCarattere(polimero, (char)(i + 'a'));
        itera(polimero);
        if(polimero.length() < bestVal){
            bestVal = polimero.length();
            best = i;
        }
    }
    cout<<"Togliendo "<<(char)(best + 'a')<<": "<<bestVal<<endl;
}
