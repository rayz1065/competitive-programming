#include <iostream>
using namespace std;

int main(){
    int N, S=0, D, am;
    string avv;
    cin>>N;
    for(int i=0; i<N; i++){
        cin>>avv;
        if(avv=="donate"){
            cin>>am;
            S+=am;
        }
        else
            cout<<S<<endl;
    }
}
