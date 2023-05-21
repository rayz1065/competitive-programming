#include <bits/stdc++.h>

using namespace std;

int main(){
    int K;
    cin>>K;
    while(K!=0){
        int X, Y;
        cin>>X>>Y;
        for(int c=0; c<K; c++){
            int a, b;
            cin>>a>>b;
            if(a>X&&b>Y)
                cout<<"NE";
            else if(a>X&&b<Y)
                cout<<"SE";
            else if(a<X&&b>Y)
                cout<<"NO";
            else if(a<X&&b<Y)
                cout<<"SO";
            else
                cout<<"divisa";
            cout<<endl;
        }
        cin>>K;
    }
}
