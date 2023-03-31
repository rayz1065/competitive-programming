using namespace std;
#include <algorithm>
void permute(int subtask, int N, int V[], int R[]){
    int i=0, j=0;
    sort(V,V+N);
    for(i=0; i<N/2; i++){
        R[j]=V[N-1-i];
        R[j+1]=V[i];
        j=j+2;
    }
    if(N%2==1){
        R[N-1]=V[(N-1)/2];
    }
}