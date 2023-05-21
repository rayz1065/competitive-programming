#include <bits/stdc++.h>
#define DECKSIZE 52

using namespace std;
fstream out;

struct cardInfo{
    char num;
    char suit;

    void stampa(){
        cout<<num<<suit<<"\n";
    }

    void stampaS(){
        cout<<num<<suit;
    }

    int getVal(){
        if(num >= '2' && num <= '9')
            return num - '0';
        return 10;
    }

    operator int(){
        return this->getVal();
    }
};
stack<cardInfo> deck;
deque<cardInfo> mano;

void iniz(){
    while(!deck.empty())
        deck.pop();
    while(!mano.empty())
        mano.pop_back();
}

int itera(){
    int X = deck.top();
    deck.pop();
    for(int i = 0; i < 10 - X; i++)
        deck.pop();
    return X;
}

int main(){
    out.open("output.txt", ios::out);
    int T;
    cin >> T;
    for(int t = 1; t <= T; t++){
        iniz();
        for(int i = 0; i < DECKSIZE; i++){
            char c[5];
            cin >> c;
            deck.push({c[0], c[1]});
        }

        for(int i = 0; i < 25; i++){
            mano.push_front(deck.top());
            deck.pop();
        }

        int Y = 0;
        for(int i = 0; i < 3; i++)
            Y+= itera();

        while(!mano.empty()){
            deck.push(mano.front());
            mano.pop_front();
        }

        while(deck.size() > Y){
            deck.pop();
        }
        cout<<"Case "<<t<<": ";
        deck.top().stampa();
    }
}
