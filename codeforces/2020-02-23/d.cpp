#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
struct cats{
    int am;
    int t;

    bool operator < (cats b) const{
        if(am < b.am) return true;
        if(b.am < am) return false;
        return t < b.t;
    }
};

int a[MAXN];
int t[MAXN];

multiset<cats> l;

long long iter(){
    int curr;
    multiset<cats>::iterator i = l.begin(), tempit;
    vector<cats> temp;
    curr = i -> am;
    //cout<<"curr = "<<i -> am<<"\n";

    while(i != l.end() && i -> am == curr){
        temp.push_back(*i);
        tempit = i++;
        l.erase(tempit);
    }
    //cout<<"ignore "<<i -> am<<", "<<i -> t<<"\n";
    int c = temp.size();

    long long s = 0;
    for(int i = 0; i < c - 1; i++){
        int inc_by = c - i - 1;
        s+= (long long) inc_by * temp[i].t;
        //cout<<"increment by "<<inc_by<<" * "<<temp[i].t<<"\n";
        l.insert({temp[i].am + inc_by, temp[i].t});
    }
    return s;
}

bool sort2(cats a, cats b){
    if(a.t < b.t) return true;
    return a.am < b.am;
}

long long iter_continui(){
    int curr, beg;
    multiset<cats>::iterator i = l.begin();
    vector<cats> temp;
    curr = beg = i -> am;
    //cout<<"curr = "<<i -> am<<"\n";

    while(i != l.end() && i -> am <= curr + 1){
        temp.push_back(*i);
        if(i -> am != curr)
            curr++;
        i++;
    }

    //cout<<"ignore "<<i -> am<<", "<<i -> t<<"\n";
    sort(curr.begin(), curr.end(), sort2);
    int c = temp.size();

    long long s = 0;
    for(int i = 0; i < c - 1; i++){
        int inc_by = c - i - 1;
        s+= (long long) inc_by * temp[i].t;
        //cout<<"increment by "<<inc_by<<" * "<<temp[i].t<<"\n";
        l.insert({temp[i].am + inc_by, temp[i].t});
    }
    return s;
}

int main(){
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    for(int i = 0; i < n; i++)
        cin >> t[i];

    for(int i = 0; i < n; i++)
        l.insert({a[i], t[i]});

    long long s = 0;
    while(l.size() > 0){
        /*for(auto j:l)
            cout<<"-> "<<j.am<<","<<j.t<<"\n";
        cout<<"\n";*/
        s+= iter();
    }
    cout<<s<<"\n";

}
