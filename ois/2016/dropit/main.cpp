#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;
int main(){
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n, caduta=0;
    cin>>n;
    vector <int> pila;
    for(int i=0; i<n; i++){
        cin>>caduta;
        while(caduta!=0){
            if(pila.size()==0){
                pila.push_back(caduta);
                caduta=0;
            }
            else if(pila[pila.size()-1]==caduta){
                pila.pop_back();
                caduta=0;
            }
            else if(pila[pila.size()-1]>caduta){
                pila.push_back(caduta);
                pila.push_back(pila[pila.size()-2]-caduta);
                caduta=0;
            }
            else{
                caduta=caduta-pila[pila.size()-1];
                pila.pop_back();
            }
        }
    }
    cout<<pila.size()<<endl;
    for(int c=0; c<pila.size()-1; c++)
        cout<<pila[c]<<" ";
    cout<<pila[pila.size()-1];
}