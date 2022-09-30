#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int n=0, t=0, x, dire;
    cin>>n>>t;
    if(n%2==1){
        int centro=0, cinbin;
        for(int i=0; i<n; i++){
            if(i+1==(n+1)/2){
                cin>>centro;
                i=n;
                cin.ignore(2000000, '\n');
            }
            else
                cin>>cinbin;
        }
        for(int i=0; i<t; i++){
            cin>>x>>dire;
            if(x>centro)
                cout<<0<<" ";
            else
                cout<<1<<" ";
        }
    }
    else{
        int leftc, rightc, cinbin;
        for(int i=0; i<n; i++){
            if(i+1==n/2){
                cin>>leftc;
                cin>>rightc;
                i=n;
                cin.ignore(2000000, '\n');
            }
            else
                cin>>cinbin;
        }
        for(int i=0; i<t; i++){
            cin>>x>>dire;
            if(x<leftc)
                cout<<1<<" ";
            else if(x>rightc)
                cout<<0<<" ";
            else
                cout<<dire<<" ";
        }
    }
}
