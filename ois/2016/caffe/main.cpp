#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n, a=0, b=0;
    cin>>n;
    vector < pair<int,char> > orari;
    orari.resize(2*n,{0,0});
    for(int i=0; i<2*n; i=i+2){
        cin>>a;
        cin>>b;
        orari[i]=make_pair(a,'a');
        orari[i+1]=make_pair(b,'l');
    }
    sort(orari.begin(),orari.begin()+2*n);
    int pres=0, tot=0;
    for(int i=0; i<2*n; i++){
        if(orari[i].second=='l')
            pres--;
        if(orari[i].second=='a'){
            pres++;
            tot+=pres;
        }
    }
    cout<<tot;
}
