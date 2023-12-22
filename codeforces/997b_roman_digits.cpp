#include <bits/stdc++.h>

using namespace std;
int romani[4] = {50, 10, 5, 1};
string lettere = "LXVI";
set<int> valori;
int p = 0;

void desc(int i, int s, int k, string rom){
    if(i == 0){
        p++;
        int uni = 0;
        for(auto r:rom)
            if(r == 'X')
                uni++;
        if(uni >= 5){
            int uni = 0;
            for(auto r:rom)
                if(r == 'V')
                    uni++;
            if(uni >= 1){
                return;
            }
        }
        //cout<<rom<<" "<<s;
        if(!valori.count(s)){
            valori.insert(s);
        }
        //else
            //cout<<" !!!!!!!!";
        //cout<<endl;
        return;
    }
    for(int j = k; j < 4; j++)
        desc(i - 1, s + romani[j], j, rom + lettere[j]);
}

int main(){
    int N;
    cin>>N;
    desc(N, 0, 0, "");
    cout<<valori.size();
    cout<<endl;
    cout<<p<<endl;
}
