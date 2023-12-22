#include <iostream>

using namespace std;



int main(){
    int N, M;
    cin>>N>>M;
    int num[N];
    for(int i=0; i<N; i++){
        cin>>num[i];
        num[i] = num[i]%M;
    }

    int S=0, Smax=0;
    ///testo capito male
    cout<<Smax;
}
