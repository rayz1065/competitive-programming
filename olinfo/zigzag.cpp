#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, a, b , cons=1, direz=0;
    cin>>n;
    cin>>a;
    for(int cont=0;cont<(n-1);cont++){
        cin>>b;
        if(direz==0){                       //la prima volta non si ha una direzione ed è necessario sceglierla
            if(a<b){
                direz=1;
            }
            if(a>b){
                direz=-1;
            }
        }
        if(direz==1){
            if(a<b){
                direz=-direz;
                cons++;
                a=b;
            }
            else{
                a=b;
            }
        }
        else{
            if(a>b){
                direz=-direz;
                cons++;
                a=b;
            }
            else{
                a=b;
            }
        }
    }
    cout<<cons;
}
