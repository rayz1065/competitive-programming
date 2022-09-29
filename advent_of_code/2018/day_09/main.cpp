#include <bits/stdc++.h>
#define MAXP 500
#define MAXN 75000
#define DEBUG 1
using namespace std;

int punti[MAXP];

int main(){
    fstream in, out;
    in.open("input9.txt", ios::in);

    char desc[100];
    in.getline(desc, 100);
    int i = 0, P = 0, N = 0;
    while(desc[i] != '\0' && desc[i] >= '0' && desc[i] <= '9')
        P = P*10 + desc[i++] - '0';
    while(desc[i] != '\0' && (desc[i] < '0' || desc[i] > '9'))
        i++;
    while(desc[i] != '\0' && desc[i] >= '0' && desc[i] <= '9')
        N = N*10 + desc[i++] - '0';

    list<int> cerchio = {0};
    auto currIterator = cerchio.begin();
    int g = -1, currMarble = 0;

    int maxScore = 0;
    if(DEBUG)
        cout<<"[-] 0\n";
    for(int i = 1; i <= N; i++){
        g = (g + 1)%P;
        if(i%23 == 0){
            int newPos = (currMarble - 7)%(cerchio.size());
            if(newPos < 0){
                currIterator = cerchio.end();
                advance(currIterator, newPos);
                newPos+= cerchio.size();
            }
            else
                advance(currIterator, -7);
            punti[g]+= i + *currIterator;
            cerchio.erase(currIterator);
            currMarble = newPos;
            maxScore = max(maxScore, punti[g]);
        }
        else{
            int newPos = (currMarble + 2)%(cerchio.size());
            if(newPos < 3){
                currIterator = cerchio.begin();
                advance(currIterator, newPos);
            }
            else
                advance(currIterator, 2);
            cerchio.insert(currIterator, {i});
            advance(currIterator, 1);
            currMarble = newPos;
        }
        if(DEBUG){
            cout<<"["<<g + 1<<"]"<<" ";
            for(auto j:cerchio)
                cout<<j<<" "<<((j < 10)?" ":"");
            cout<<endl;
        }
    }
    cout<<maxScore<<endl;
}
