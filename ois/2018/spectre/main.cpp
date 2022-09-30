#include <bits/stdc++.h>
#define getchar_unlocked getchar
using namespace std;

string getWord(){
    string S;
    char c = getchar_unlocked();
    while(c == ' ' || c == '\n')
        c = getchar_unlocked();
    while(c != ' ' && c != '\n'){
        S+= c;
        c = getchar_unlocked();
    }
    return S;
}

int main(){
    unordered_set<string> mancanti;
    int N, S = 0;
    cin>>N;
    for(int i = 0; i < N; i++){
        string a, b, c;
        a = getWord();
        cin>>b;
        b = getWord();
        cin>>c;
        c = getWord();
        if(mancanti.find(b) == mancanti.end() && mancanti.find(c) == mancanti.end())
            S++;
        mancanti.insert(a);
    }
    cout<<S;
}
