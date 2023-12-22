#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;

typedef long long int lli;

int rulenum;
int n = 0;

map<string, int> elementi;

vector<int> grafo[MAXN];
string nome[MAXN];
bool visited[MAXN];

stack<int> topoOrder;

int nodeIndex(string s){
    if(elementi.find(s) != elementi.end())
        return elementi[s];
    nome[n] = s;
    return elementi[s] = n++;
}

void topoSort(int node){
    if(visited[node]) return;
    visited[node] = true;
    for(auto j:grafo[node])
        topoSort(j);
    topoOrder.push(node);
}

int main(){
    cin >> rulenum;
    string a;
    getline(cin, a);
    for(int i = 0; i < rulenum; i++){
        getline(cin, a);
        a+= ' ';
        int toCompile;
        int lastRuleBeg = 0;
        for(int j = 0; j < a.length(); j++){
            if(a[j] == ':'){
                toCompile = nodeIndex(a.substr(lastRuleBeg, j));
                lastRuleBeg = j + 2;
                j+= 1;

            }
            else if(a[j] == ' '){
                string lst = a.substr(lastRuleBeg, j - lastRuleBeg);
                grafo[nodeIndex(lst)].push_back(toCompile);
                lastRuleBeg = j + 1;
            }
        }
    }
    cin>>a;
    int root = nodeIndex(a);
    topoSort(root);
    while(!topoOrder.empty()){
        int node = topoOrder.top();
        cout<<nome[node]<<"\n";
        topoOrder.pop();
    }
}
