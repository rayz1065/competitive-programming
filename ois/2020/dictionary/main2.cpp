#include <bits/stdc++.h>
#define MAXN 1005

using namespace std;

int n, d;
string words[MAXN];
unordered_map<string, int> word_id;
vector<int> definitions[MAXN];
vector<int> req_by[MAXN];
vector<int> req_for[MAXN];
int learnable_words;

bool known[MAXN];
int forget_order[MAXN];

vector<int> best_sol;

int next_word_id = 0;
int get_word_id (string a){
    if(word_id.count(a) == 1) {
        return word_id[a];
    }
    words[next_word_id] = a;
    return word_id[a] = next_word_id++;
}

enum {
    UNVISITED,
    VISITING,
    VISITED
} visit_state[MAXN];

int _re_learn_crit (int node) {
    if (known[node] || visit_state[node] == VISITED) {
        // cout << "Already learnt " << words[node] << "\n";
        // already learnt
        return -1;
    }
    if (req_for[node].size() == 0 || visit_state[node] == VISITING) {
        return -2;
    }
    visit_state[node] = VISITING;
    // cout << "Trying to re-learn " << words[node] << "\n";
    for (auto j: req_for[node]) {
        int res = _re_learn_crit(j);
        if (res == -2) {
            // cout << "Can't re-learn " << words[node] << ": i need " << words[j] << ", returning " << node << "\n";
            return node;
        } else if (res != -1) {
            return res;
        }
    }
    visit_state[node] = VISITED;
    return -1;
}

int re_learn_crit (int node) {
    fill(visit_state, visit_state + n, UNVISITED);
    return _re_learn_crit(node);
}

bool can_learn (int node) {
    int res = re_learn_crit(node);
    return res == -1;
}

void try_forgetting () {
    for (int k = 0; k < learnable_words; k++) {
        int i = forget_order[k];
        // cout << "Trying to forget " << words[i] << "\n";
        known[i] = false;
        int res = re_learn_crit(i);
        if (res != -1) {
            known[i] = true;
        }
    }
}

void solve () {
    // learns every word
    fill(known, known + n, true);
    random_shuffle(forget_order, forget_order + learnable_words);
    // forgets words in order
    try_forgetting();

    // exchange 1 word for 1 with no extra cost
    for (int k = 0; k < learnable_words; k++) {
        int i = forget_order[k];
        if (known[i]) {
            // why do i know this word...
            known[i] = false;
            int j = re_learn_crit(i);
            if (j == -1) {
                // saved a word!
                continue ;
            }
            // because of word j
            known[j] = true;
            if (!can_learn(i)) {
                // not sufficient
                known[j] = false;
                known[i] = true;
            }
        }
    }

    // try forgetting even more
    try_forgetting();
    vector<int> curr_sol;
    for (int i = 0; i < n; i++) {
        if (known[i]) {
            curr_sol.push_back(i);
        }
    }
    if (curr_sol.size() < best_sol.size()) {
        best_sol = curr_sol;
    }
}

chrono::_V2::system_clock::time_point start_time;
bool is_timeout () {
#ifdef DEBUG
    return false;
#endif
    auto elapsed = chrono::high_resolution_clock::now() - start_time;
    long long milliseconds = chrono::duration_cast<std::chrono::milliseconds>(
            elapsed).count();
    return milliseconds > 1500;
}

int main (){
    start_time = chrono::high_resolution_clock::now();

    cin >> n >> d;
    learnable_words = 0;
    for(int i = 0; i < d; i++){
        string new_word;
        int k;
        cin >> new_word >> k;
        int nwid = get_word_id(new_word);
        if (k > 0) {
            forget_order[learnable_words++] = nwid;
        }
        while(k--){
            string def_word;
            cin >> def_word;
            definitions[nwid].push_back(get_word_id(def_word));
            req_by[get_word_id(def_word)].push_back(nwid);
            req_for[nwid].push_back(get_word_id(def_word));
        }
    }
    for (int i = 0; i < n; i++) {
        // compute a very basic solution
        best_sol.push_back(i);
    }

    srand(1065);
    for (int i = 0; i < 10 && !is_timeout(); i++) {
        solve();
    }

    cout << best_sol.size() << "\n";
    for(auto i: best_sol) {
        cout << words[i] << "\n";
    }
}
