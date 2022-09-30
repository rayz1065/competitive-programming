#include <bits/stdc++.h>

using namespace std;

int N, K, L;
unordered_set<string> avoid;
unordered_map<string, int> depth;
map<string, set<char> > sottos;
map<string, vector<string> > grafo;
string soluzione;

int discesa(string nodo){
    if(soluzione.size() == L){
        cout<<soluzione;
        exit(0);
    }
    depth[nodo] = L;
    int maxDepth = 1;
    for(auto i:grafo[nodo]){
        if(depth[i] + soluzione.size() >= L){
            soluzione+= i[i.size() - 1];
            discesa(i);
        }
    }
    for(auto i:grafo[nodo]){
        if(depth[i] == 0){
            soluzione+= i[i.size() - 1];

            int d = discesa(i);
            maxDepth = max(d, maxDepth);
            soluzione.pop_back();
        }
        else
            maxDepth = max(depth[i] + 1, maxDepth);
    }
    depth[nodo] = maxDepth;
    return depth[nodo] + 1;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(false);
    cin>>N>>K>>L;

    for(int i = 0; i < N; i++){
        string word, b;
        cin>>word;
        for(int i = 0; i < K && i < word.size(); i++)
            b+= word[i];
        for(int i = K; i < word.size(); i++){
            b+= word[i];
            avoid.insert(b);
            b.erase(b.begin());
        }
        b = "";
        for(int i = 0; i < K - 1 && i < word.size(); i++)
            b+= word[i];
        for(int i = K - 1; i < word.size(); i++){
            sottos[b].insert(word[i]);
            b+= word[i];
            b.erase(b.begin());
        }
    }

    for(auto i:sottos){
        for(auto j:i.second){
            string nextNode = i.first + j;
            string memo = nextNode;
            nextNode.erase(nextNode.begin());
            for(auto z:sottos[nextNode]){
                if(!avoid.count(memo + z)){
                    grafo[memo].push_back(nextNode + z);
                }
            }

        }
    }

    for(auto i:grafo){
        soluzione = i.first;
        depth[i.first] = L;
        depth[i.first] = discesa(i.first);
    }
}
