#define MAXN 750005
using namespace std;
int N;
int fenwick[MAXN];

void update(int k){
    while(k<=N/2+1){
        fenwick[k]++;
        k+=k&(-k);
    }
}

int somma(int k){
    int S=0;
    while(k>0){
        S+=fenwick[k];
        k-=k&(-k);
    }
    return S;
}

long long paletta_sort(int A, int V[]){
    N = A;
    for(int i=0; i<N; i++)
        if(V[i]%2 != i%2)
            return -1;

    long long S=0;
    for(int i=0; i<N; i+=2){
        S+=i/2-somma(V[i]/2+1);
        update(V[i]/2+1);
    }
    for(int i=0; i<N/2+1; i++)
        fenwick[i]=0;

    for(int i=1; i<N; i+=2){
        S+=i/2-somma(V[i]/2+1);
        update(V[i]/2+1);
    }
    return S;
}
