#include <bits/stdc++.h>
#define MAXN 101
using namespace std;

vector<int> grafo[MAXN];
int dist[MAXN];

void BFS(int a){
    queue<int> FF;
    FF.push(a);
    dist[a]=0;
    while(!FF.empty()){
        int nodo=FF.front();
        int val=dist[nodo]+1;
        FF.pop();
        for(int i=0; i<grafo[nodo].size(); i++){
            if(dist[grafo[nodo][i]]>val){
                dist[grafo[nodo][i]]=val;
                FF.push(grafo[nodo][i]);
            }
        }
    }
}

int main(){
    cout.setf(ios::fixed,ios::floatfield);
    cout.precision(3);
    int a, b;
    cin>>a>>b;
    set<int> pagine;
    for(int c=1; a!=0&&b!=0; c++){
        for(int i=0; i<=100; i++){
            grafo[i].clear();
            dist[i]=100000;
        }
        pagine.clear();

        while(a!=0&&b!=0){
            pagine.insert(a);
            pagine.insert(b);
            grafo[a].push_back(b);
            cin>>a>>b;
        }

        double media=0;
        for(auto it:pagine){
            BFS(it);
            for(auto jt:pagine){
                media+=dist[jt];
                dist[jt]=100000;
            }
        }
        cout<<"Case "<<c<<": average length between pages = "<<media/(pagine.size()*pagine.size()-pagine.size())<<" clicks"<<endl;
        cin>>a>>b;
    }
}
