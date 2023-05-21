#include <bits/stdc++.h>

using namespace std;

int main(){
    int T;
    cin>>T;
    for(int i=0; i<T; i++){
        char numb[1000];
        int mod[3];
        for(int i=0; i<3; i++)
            mod[i]=0;
        cin>>numb;
        for(int i=0; i<strlen(numb); i++)
            mod[(numb[i]-'0')%3]++;

        int S=(mod[1]+mod[2]*2)%3;
        cout<<"Case "<<i+1<<": ";
        if(S==0)
            cout<<((mod[0]%2==0)?'T':'S');
        else if(mod[S]==0&&strlen(numb)>1)
            cout<<'T';
        else
            cout<<((mod[0]%2==0)?'S':'T');
        cout<<endl;
    }
}
