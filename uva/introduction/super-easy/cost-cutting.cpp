#include <iostream>
#define dim 20
using namespace std;

int main(){
    int T;
    cin>>T;
    for(int i=0; i<T; i++){
        int A, B, C;
        cin>>A>>B>>C;
        if(A>B)
            swap(A, B);
        if(A>C)
            swap(A, C);
        cout<<"Case "<<i+1<<": "<<min(B, C)<<endl;
    }
}
