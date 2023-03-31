#include <bits/stdc++.h>
#define MAXN 1005
#define MAXM 1005
#define MOD 1000000007

using namespace std;

int n, m;
int curr[MAXN];

enum EsoType {
    VALUE,
    ROUND = -1,
    SQUARED = -3,
};

struct Eso {
    EsoType type;
    int value;
    vector<Eso> children;

    bool operator == (const Eso &other) const {
        if (this->type != other.type || this->value != other.value || this->children.size() != other.children.size()) {
            return false;
        }
        for (int i = 0; i < children.size(); i++) {
            if (!(this->children[i] == other.children[i])) {
                return false;
            }
        }
        return true;
    }
} expressions[MAXM];

int hash_eso (const Eso &eso) {
    if (eso.type == VALUE) {
        return eso.value;
    }
    size_t hsh = eso.type * (-17);
    for (auto i: eso.children) {
        hsh = ((hsh * 17) + hash_eso(i)) % MOD;
    }
    return hsh;
}

namespace std {
    template <> struct hash<Eso>
    {
        size_t operator()(const Eso &eso) const {
            return hash_eso(eso);
        }
    };
}

unordered_map<Eso, vector<int>> eso_freq;

Eso parse_eso (int &i) {
    // read the type
    int closing = curr[i] - 1;
    Eso eso = { (EsoType) curr[i++] };

    while (curr[i] != closing) {
        if (curr[i] < 0) {
            // opening par
            Eso child = parse_eso(i);
            eso.children.push_back(child);
        } else {
            eso.children.push_back({ VALUE, curr[i++] });
        }
    }
    // found closing
    i++;
    return eso;
}

bool comp_eso (Eso a, Eso b) {
    return a.value < b.value;
}

void print_eso (Eso eso) {
    if (eso.type == VALUE) {
        cout << eso.value << " ";
        return ;
    }
    cout << (eso.type == -1 ? '(' : '[') << " ";
    for (auto i: eso.children) {
        print_eso(i);
    }
    cout << (eso.type == -1 ? ')' : ']') << " ";
}

Eso normalize (Eso &original) {
    if (original.type == VALUE) {
        return original;
    }
    Eso eso = { original.type };
    for (int i = 0; i < original.children.size(); i++) {
        eso.children.push_back(normalize(original.children[i]));
    }
    if (eso.type == ROUND) {
        // values can be sorted
        sort(eso.children.begin(), eso.children.end(), comp_eso);
    } else if (eso.type == SQUARED) {
        // just find smallest first/last value
        if (eso.children.begin()->value > eso.children.rbegin()->value) {
            // put the smallest value first
            reverse(eso.children.begin(), eso.children.end());
        }
    }

    // compute the value
    eso.value = eso.children[0].value;
    return eso;
}

int main () {
    fstream in, out;
    in.open("input.txt", ios::in);
    out.open("output.txt", ios::out);

    in >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            in >> curr[j];
        }
        int parse_idx = 0;
        expressions[i] = parse_eso(parse_idx);
        // print_eso(expressions[i]);
        // cout << "\n";
        expressions[i] = normalize(expressions[i]);
        // print_eso(expressions[i]);
        // cout << "\n";
        // cout << "hash is " << hash_eso(expressions[i]) << "\n";
        eso_freq[expressions[i]].push_back(i + 1);
    }
    out << eso_freq.size() << "\n";
    for (auto i: eso_freq) {
        out << i.second.size();
        for (auto idx: i.second) {
            out << " " << idx;
        }
        out << "\n";
    }
}
