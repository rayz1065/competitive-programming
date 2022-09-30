#include <bits/stdc++.h>
#ifdef _WIN32
    #define getchar_unlocked getchar
#endif // _WIN32
using namespace std;

struct infoCarta{
    int guadagno;
    short valore;
    int rimanenti;
    int prezzo;
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M, T;
    cin>>N>>M>>T;
    queue<int> mazzo;
    map<int, int> prezzi;
    infoCarta carte[N];
    for(int i = 0; i < M; i++){
        int carta;
        cin>>carta;
        mazzo.push(carta);
    }

    for(int i = 0; i < N; i++){
        cin>>carte[i].rimanenti>>carte[i].prezzo>>carte[i].guadagno>>carte[i].valore;
        if(carte[i].rimanenti > 0)
            prezzi[carte[i].prezzo] = i;
    }

    int topCards[5];
    for(int i = 0; i < T; i++){
        int R = 0;
        for(int j = 0; j < 5; j++){
            topCards[j] = mazzo.front();
            R+= carte[topCards[j]].guadagno;
            mazzo.pop();
        }
        int bestCard = (--prezzi.upper_bound(R))->second;

        mazzo.push(bestCard);
        carte[bestCard].rimanenti--;
        if(carte[bestCard].rimanenti == 0)
            prezzi.erase(carte[bestCard].prezzo);

        for(int j = 0; j < 5; j++){
            mazzo.push(topCards[j]);
        }
    }
    int S = 0;
    while(!mazzo.empty()){
        S+= carte[mazzo.front()].valore;
        mazzo.pop();
    }
    cout<<S;
}
