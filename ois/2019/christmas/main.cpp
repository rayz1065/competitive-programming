#include <bits/stdc++.h>
#define MAXN 105
#define MAXB 12000
using namespace std;

bool canReach[MAXN][MAXB];
int regali[MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, B;
    cin>>N>>B;

    for(int i = 0; i < N; i++)
        cin>>regali[i]; /// prendiamo tutti i regali in input

    canReach[0][0] = true; /// sappiamo che una somma totale di 0 la possiamo avere
    canReach[0][regali[0]] = true; /// possiamo anche avere una somma totale uguale al primo regalo

    int maxVal = 0; /// variabile che contiene il valore massimo
    for(int i = 1; i < N; i++){ /// aggiungiamo uno alla volta i regali
        for(int j = 0; j < MAXB; j++){ /// passiamo per ogni prezzo
            if(canReach[i - 1][j]){ /// se potevamo ottenere la somma anche senza il regalo attuale allora possiamo ottenerla ancora
                canReach[i][j] = true;
            }
            else if(j - regali[i] >= 0 && canReach[i - 1][j - regali[i]]){ /// altrimenti vediamo se possiamo ottenere la somma - regalo[j] possiamo ottenere anche la somma
                maxVal = max(maxVal, j); /// esempio, se con i regali precedenti potevamo ottenere la somma "3", e ora abbiamo un regalo di prezzo "2", possiamo anche ottenere la somma "5"
                canReach[i][j] = true;
            }
        }
    }

    if(maxVal >= B){ /// si può fare anche direttamente nella parte principale del programma ma anche così funziona bene
        for(int i = B; i < maxVal; i++)
            if(canReach[N - 1][i]){
                cout<<i;
                return 0;
            }
    }
    else /// se non possiamo superare il budget, dovremo accontentarci di comprare tutti i regali ottenendo una somma di maxVal
        cout<<maxVal;
}
