#include <cstdio>
#include <iostream>
#include <set>
#include <queue>

using namespace std;
int main(){
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int n;
    cin>>n;
    queue<pair<int,int> > q1;
    queue<pair<int,int> > q2;
    set<pair<int,int> >s1;
    set<pair<int,int> >s2;
    for(int i=0; i<n; i++){
        int num;
        cin>>num;
        q1.push({num,i});
        s1.insert({num,i});
    }
    for(int i=0; i<n; i++){
        int num;
        cin>>num;
        q2.push({num,i+n});
        s2.insert({num,i+n});
    }
    int minimo[2*n], massimo[2*n];
    for(int c=0; c<2*n; c++){
        q1.push(q2.front());
        q2.push(q1.front());
        s1.insert(q2.front());
        s2.insert(q1.front());
        s1.erase(q1.front());
        s2.erase(q2.front());
        q1.pop();
        q2.pop();
        minimo[c]=s1.begin()->first;
        massimo[c]=s2.rbegin()->first;
    }
    int q;
    cin>>q;
    int giradi, giratot=0;
    for(int c=0; c<q; c++){
        cin>>giradi;
        giratot=(giradi+giratot)%(2*n);
        cout<<minimo[2*n-giratot-1]<<" "<<massimo[2*n-giratot-1]<<endl;
    }
}
