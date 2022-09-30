#include <cstdio>
#include <iostream>

using namespace std;
int main(){
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int n, t, k;
    cin>>n>>t>>k;
    int nextest, dastud=k, anno[3000]={0}, oldtest=0, arg=k;
    if(t<k){
        cout<<-1;
        return 0;}
    else if(n>1){
        cin>>nextest;
        nextest+=1000;
        for(int c=nextest-1; nextest-c<=k; c--){
            anno[c]=1;
        }
        oldtest=nextest;
        for(int c=0; c<n-1; c++){
            cin>>nextest;
            nextest+=1000;
            for(int j=oldtest-t; j<nextest-t; j++){
                if(anno[j]==1)
                    arg--;
            }
            oldtest=nextest;
            dastud+=k-arg;
            while(arg<k){
                anno[nextest-1]=1;
                arg++;
                nextest--;
            }
        }
    }
    cout<<dastud;
}
