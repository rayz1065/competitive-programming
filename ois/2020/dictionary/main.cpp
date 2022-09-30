#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

int n, d;
string words[MAXN];
map<string, int> word_id;
vector<int> definitions[MAXN];
vector<int> reqby[MAXN];

int curr_word_id = 0;

bool known[MAXN];
bool is_missing[MAXN];

int get_word_id(string a){
    if(word_id.count(a) == 1)
        return word_id[a];
    words[curr_word_id] = a;

    return word_id[a] = curr_word_id++;
}

int maxdepth = 0;

bool can_understand(int i, int depth){
    if(known[i])
        return true;
    if(depth < 0) return false;
    if(definitions[i].size() == 0)
        return false;
    for(auto j:definitions[i])
        if(!can_understand(j, depth - 1)) return false;
    return true;
}

bool can_understand(int i){
    return can_understand(i, maxdepth);
}

int count_known(){
    int s = 0;
    for(int i = 0; i < n; i++)
        s+= can_understand(i);
    return s;
}

void learn(int i){
    //cout<<"learn "<<words[i]<<" ("<<count_known()<<")\n";
    known[i] = true;
    for(auto j:reqby[i]){
        if(!known[j] && can_understand(j, 0))
            learn(j);
    }
}

void forget(int i){
    //cout<<"forget "<<words[i]<<"\n";
    known[i] = false;
    for(auto j:reqby[i]){
        if(!is_missing[j] && known[j])
            forget(j);
    }
}

void add_to_know(int i){
    //cout<<"add to know "<<words[i]<<"\n";
    is_missing[i] = true;
    learn(i);
}

void rem_to_know(int i){
    is_missing[i] = false;
    forget(i);
}

bool add_words(){
    bool added = false;
    for(int i = 0; i < n; i++)
        if(!known[i] && can_understand(i)){
            known[i] = added = true;
        }

    return added;
}

int ordine[MAXN];

int best_score = MAXN;
vector<int> best_sol;

int count_unk(int i){
    if(can_understand(i))
        return 0;

    int s = 0;
    for(auto j:definitions[i])
        if(!can_understand(j)) s++;
    return s;
}

int count_cbl(int i){
    if(can_understand(i))
        return 0;

    int a = count_known();
    known[i] = true;
    int b = count_known();
    known[i] = false;

    return b - a;
}

int cbl[MAXN], unk[MAXN];

void recalc(){
    for(int i = 0; i < n; i++)
        cbl[i] = count_cbl(i),
        unk[i] = count_unk(i);
}

bool comp(int i, int j){
    if(can_understand(i) && can_understand(j))
        return i < j;
    if(can_understand(i))
        return false;
    if(can_understand(j))
        return true;

    if(cbl[i] > cbl[j]) return true;
    if(cbl[i] < cbl[j]) return false;

    if(unk[i] > unk[j]) return true;
    if(unk[j] < unk[i]) return false;

    return i < j;
}

int count_missing(){
    int s = 0;
    for(int i = 0; i < n; i++)
        s+= is_missing[i];
    return s;
}

int iter = 0;

void save_sol(){
    if(count_missing() < best_score){
        best_score = count_missing();
        best_sol.clear();
        for(int i = 0; i < n; i++){
            if(is_missing[i])
                best_sol.push_back(i);
        }
    }
}

void solve2(int i){
    if(iter > 1000000) return ;

    if(i == n){
        if(count_known() == n)
            save_sol();
        iter++;
        return ;
    }
    int c = ordine[i];
    /*cout<<i<<": "<<words[i]<<"\n";
    for(int j = 0; j < n; j++)
        cout<<known[j]<<" ";
    cout<<"\n";
    for(int j = 0; j < n; j++)
        cout<<is_missing[j]<<" ";
    cout<<"\n\n";*/

    if(can_understand(c)){
        solve2(i + 1);
        return ;
    }

    add_to_know(c);
    solve2(i + 1);
    rem_to_know(c);

    solve2(i + 1);
}

void solve(){
    for(int i = 0; i < n; i++)
        if(definitions[i].size() == 0)
            add_to_know(i);

    while(add_words());
    recalc();
    sort(ordine, ordine + n, comp);

    for(int i = 0; i < n; i++){
        int curr = ordine[i];

        if(!can_understand(curr)){
            add_to_know(curr);
        }

        while(add_words());
    }
}

void init(){
    fill(is_missing, is_missing + n, false);
    fill(known, known + n, false);
    for(int i = 0; i < n; i++)
        if(definitions[i].size() == 0)
            add_to_know(i);
}

int main(){
    cin >> n >> d;
    for(int i = 0; i < d; i++){
        string new_word;
        cin >> new_word;
        int nwid = get_word_id(new_word);

        int k;
        cin >> k;
        while(k--){
            string def_word;
            cin >> def_word;
            definitions[nwid].push_back(get_word_id(def_word));
            reqby[get_word_id(def_word)].push_back(nwid);
        }
    }

    //srand(time(NULL));

    for(int i = 0; i < n; i++)
        ordine[i] = i;
    sort(ordine, ordine + n, comp);
    //init();
    //solve();
    //save_sol();

    init();
    solve2(0);

    cout<<best_score<<"\n";
    for(auto i:best_sol)
        cout<<words[i]<<"\n";
}
