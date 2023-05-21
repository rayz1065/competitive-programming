#include <bits/stdc++.h>
#define MAXLINE 40
#define MAXMANO 13

using namespace std;
char poss[] = "SHDC";

struct carta{
    char cardRank;
    int cardSuit;

    void stampa(){
        cout<<cardRank<<" di "<<poss[cardSuit]<<"\n";
    }

    bool operator == (const char c){
        return (cardRank == c);
    }
} mano[MAXMANO + 1];

bool stopped[4];
int cartePerSuit[4];

void contaPerSemi(){
    for(int i = 0; i < MAXMANO; i++)
        cartePerSuit[mano[i].cardSuit]++;
}

int valutaQuattro(){
    contaPerSemi();
    // Each ace counts 4 points. Each king counts 3 points. Each queen counts 2 points. Each jack counts one point.
    int punti = 0;
    for(int i = 0; i < MAXMANO; i++){
        if(mano[i].cardRank == 'A')
            punti+= 4, stopped[mano[i].cardSuit] = true;
        else if(mano[i].cardRank == 'K')
            punti+= 3;
        else if(mano[i].cardRank == 'Q')
            punti+= 2;
        else if(mano[i].cardRank == 'J')
            punti+= 1;
    }
    // Subtract a point for any king of a suit in which the hand holds no other cards.
    for(int i = 0; i < MAXMANO; i++){
        if(mano[i] == 'K'){
            if(cartePerSuit[mano[i].cardSuit] == 1)
                punti-= 1;
            else
                stopped[mano[i].cardSuit] = true;
        }
    }
    // Subtract a point for any queen in a suit in which the hand holds only zero or one other cards.
    for(int i = 0; i < MAXMANO; i++){
        if(mano[i] == 'Q'){
            if(cartePerSuit[mano[i].cardSuit] <= 2)
                punti-= 1;
            else
                stopped[mano[i].cardSuit] = true;
        }
    }
    // Subtract a point for any jack in a suit in which the hand holds only zero, one, or two other cards.
    for(int i = 0; i < MAXMANO; i++){
        if(mano[i] == 'J' && cartePerSuit[mano[i].cardSuit] <= 3){
            punti-= 1;
        }
    }
    return punti;
}

int valutaUltTre(){
    int punti = 0;
    /*
        5. Add a point for each suit in which the hand contains exactly two cards.
        6. Add two points for each suit in which the hand contains exactly one card.
        7. Add two points for each suit in which the hand contains no cards
    */
    for(int i = 0; i < 4; i++){
        if(cartePerSuit[i] == 2)
            punti+= 1;
        else if(cartePerSuit[i] <= 1)
            punti+= 2;
    }
    return punti;
}

int getSuit(char c){
    for(int i = 0; i < 4; i++)
        if(c == poss[i])
            return i;
    return -1;
}

bool checkNoTrump(int punti){
    if(punti < 16)
        return false;
    for(int i = 0; i < 4; i++)
        if(!stopped[i])
            return false;
    return true;
}

char getBidSuit(){
    int m = *max_element(cartePerSuit, cartePerSuit + 4);
    for(int i = 0; i < 4; i++)
        if(cartePerSuit[i] == m)
            return poss[i];
    assert(false);
    return '0'; // neh
}

int main(){
    char carte[MAXLINE];

    while(cin.getline(carte, MAXLINE)){
        fill(stopped, stopped + 4, false);
        fill(cartePerSuit, cartePerSuit + 4, false);
        for(int i = 0; i < MAXMANO; i++){
            mano[i].cardRank = carte[i*3];
            mano[i].cardSuit = getSuit(carte[i*3 + 1]);
        }

        int punti = valutaQuattro();
        if(checkNoTrump(punti))
            cout<<"BID NO-TRUMP\n";
        else{
            punti+= valutaUltTre();
            if(punti >= 14)
                cout<<"BID "<<getBidSuit()<<"\n";
            else
                cout<<"PASS\n";
        }
    }
}
