#include<bits/stdc++.h>
#define ALF 26
using namespace std;

string output;
int WM;

struct trieNode{
    trieNode *childrens[ALF];
    bool wordEnd;
    int prof;
};

trieNode *getNode(){
    trieNode *newNode = new trieNode;
    for(int i = 0; i < ALF; i++)
        newNode->childrens[i] = NULL;
    newNode->wordEnd = false;
    newNode->prof = 1;
    return newNode;
}

void insert(trieNode *root, string key){
    int N = key.size();
    trieNode *ptemp = root;
    root -> prof = max(root -> prof, N + 1);
    for(int i = 0; i < N; i++){
        int k = key[i] - 'a';
        if(ptemp->childrens[k] == NULL){
            ptemp->childrens[k] = getNode();
        }
        ptemp = ptemp->childrens[k];
        ptemp -> prof = max(ptemp -> prof, N - i);
    }
    ptemp->wordEnd = true;
}

void desc(trieNode *ptemp){
    if(ptemp->wordEnd){
        output+= "P";
        WM--;
    }
    if(ptemp -> prof == 1)
        return;
    int worstCase = 0, worstD = 0;
    for(int i = 0; i < ALF; i++){
        if(ptemp->childrens[i] != NULL){
            int d = ptemp->childrens[i]->prof;
            if(d > worstD){
                worstD = d;
                worstCase = i;
            }
        }
    }
    for(int i = 0; i < ALF; i++){
        if(i != worstCase && ptemp->childrens[i] != NULL){
            output+=(char)('a' + i);
            desc(ptemp->childrens[i]);
            if(WM > 0)
                output+= "-";
        }
    }
    output+= (char)('a' + worstCase);
    desc(ptemp->childrens[worstCase]);
    if(WM > 0)
        output+= "-";
}

int main(){
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);
    int N;
    in>>N;
    WM = N;
    trieNode *root = getNode();

    for(int i = 0; i < N; i++){
        string word;
        in>>word;
        insert(root, word);
    }
    desc(root);
    out<<output.size()<<"\n";
    for(int i = 0; i < output.size(); i++)
        out<<output[i]<<"\n";
}
