#include <bits/stdc++.h>
#define MAXN 100005
using namespace std;

int n, m, k;
int tape[MAXN];
int padre[MAXN];
bool isTaped[MAXN];
pair<int, int> distances[MAXN];

int getPadre(int nodo){
    if(padre[nodo] != nodo)
        return padre[nodo] = getPadre(padre[nodo]);
    return nodo;
}

void mergeNodes(int a, int b){
    int padreA = getPadre(a), padreB = getPadre(b);
    if(padreA != padreB)
        padre[padreA] = padreB;
    isTaped[padreB] = true;
}

int main(){
    cin >> n >> m >> k;

    for(int i = 0; i < n; i++)
        cin >> tape[i];

    for(int i = 0; i < n; i++)
        padre[i] = i;
    for(int i = 1; i < n; i++)
        distances[i - 1] = {tape[i] - tape[i - 1], i};

    sort(distances, distances + n - 1);

    int freeNodes = n, prezzo = 0, curr = 0;
    while(freeNodes > k){
        //cout<<"merging "<<distances[curr].second<<" and "<<distances[curr].second - 1<<endl;
        mergeNodes(distances[curr].second, distances[curr].second - 1);
        prezzo+= distances[curr].first - 1;
        curr++;
        freeNodes--;
    }

    cout<<prezzo + n<<endl;
}
