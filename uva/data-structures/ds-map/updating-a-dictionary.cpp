#include <bits/stdc++.h>
#define MAXL 105

using namespace std;

map<string, string> old_dict, new_dict;

char input[MAXL];

void input_dict(map<string, string> &dict){
    dict.clear();

    while(getchar() != '{');

    string key, val;
    cin.getline(input, MAXL);

    int i = 0;

    while(i < MAXL && input[i] != '}'){
        key.clear(), val.clear();
        if(input[i] < 'a' || input[i] > 'z') i++;
        while(input[i] != ':')
            key.push_back(input[i++]);
        while(input[i] != ',' && input[i] != '}')
            val.push_back(input[i++]);
        dict[key] = val;
    }
}

void init(){
    input_dict(old_dict);
    input_dict(new_dict);
}

//fstream out;
//#define cout out

void solve(){
    bool add = 0, rem = 0, cgd = 0;
    /*cout<<"new dict:\n";
    for(auto i:new_dict)
        cout<<i.first<<" -> "<<i.second<<"\n";
    cout<<"old dict:\n";
    for(auto i:old_dict)
        cout<<i.first<<" -> "<<i.second<<"\n";*/

    for(auto i:new_dict){
        if(old_dict.count(i.first) == 0){
            if(!add)
                add = true, cout<<"+";
            else
                cout<<",";
            cout<<i.first;
        }
    }
    if(add) cout<<"\n";

    for(auto i:old_dict){
        if(new_dict.count(i.first) == 0){
            if(!rem)
                rem = true, cout<<"-";
            else
                cout<<",";
            cout<<i.first;
        }
    }
    if(rem) cout<<"\n";

    for(auto i:new_dict){
        if(old_dict.count(i.first) == 1 && i.second != old_dict[i.first]){
            if(!cgd)
                cgd = true, cout<<"*";
            else
                cout<<",";
            cout<<i.first;
        }
    }
    if(cgd) cout<<"\n";

    if(!cgd && !add && !rem)
        cout<<"No changes\n";
}

int main(){
    //out.open("output.txt", ios::out);
    int n;
    cin >> n;

    while(n--){
        init();
        solve();
        /*if(n)*/ cout<<"\n";
    }
}
