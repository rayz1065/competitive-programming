#include <bits/stdc++.h>
#define MAXL 13

using namespace std;

vector<int> all_combs;
vector<int> valid_guesses;
struct Dt {
    int d;
    int subdts[MAXL + 1];
    vector<int> possibilities;
};
vector<Dt> dts;

void _find_combs (int i, int curr, int sz, vector<int> &options, vector<int> &res) {
    if (i == sz) {
        res.push_back(curr);
        return ;
    }
    for (auto j: options) {
        _find_combs(i + 1, curr << 2 | j, sz, options, res);
    }
}

void find_combs (int sz) {
    vector<int> options = { 1, 2, 3 };
    _find_combs(0, 0, sz, options, all_combs);
    options.pop_back();
    _find_combs(0, 0, sz, options, valid_guesses);
}

int find_eq (int &a, int &b) {
    // assume that one integer does not contain '11' pairs
    return __builtin_popcount(a & b);
}


pair<double, int> score (Dt &dt) {
    double s = 0;
    int tot_am = 0;
    if (dt.subdts[0] == -1) {
        return { 0, 1 };
    } else if (dt.possibilities.size() > 0) {
        int n = dt.possibilities.size();
        tot_am += n;
        if (n > 0) {
            s += n * log(n);
        }
    }
    else {
        // already expanded
        for (int i = 0; i < MAXL + 1; i++) {
            if (dt.subdts[i] <= 0) continue ;
            auto sub = score(dts[dt.subdts[i]]);
            tot_am += sub.second;
            s += sub.second * sub.first;
        }
    }
    return { s / tot_am + 1, tot_am };
}

double score_spl (Dt **spl) {
    double s = 0;
    int tot_am = 0;
    for (int i = 0; i < MAXL + 1; i++) {
        int n = spl[i]->possibilities.size();
        tot_am += n;
        if (n > 0) {
            s += n * log(n);
        }
    }
    return s / tot_am + 1;
}

Dt** split (int dt, int guess) {
    Dt** subs = new Dt*[MAXL + 1]();
    for (int i = 0; i < MAXL + 1; i++) {
        subs[i] = new Dt();
        subs[i]->d = -1;
    }
    for (auto comb: dts[dt].possibilities) {
        int eq = find_eq(comb, guess);
        subs[eq]->possibilities.push_back(comb);
    }
    return subs;
}

void alloc_spl (int dt, Dt** subs) {
    for (int i = 0; i < MAXL + 1; i++) {
        dts[dt].subdts[i] = 0;
        if (subs[i]->possibilities.size() > 0) {
            // allocate new DT
            dts.push_back(*(subs[i]));
            dts[dt].subdts[i] = dts.size() - 1;
        }
    }
}

void delete_spl (Dt **spl) {
    for (int i = 0; i < MAXL + 1; i++) {
        delete spl[i];
    }
    delete spl;
}

void find_guess (int dt, int depth) {
    // cout << dt << " " << depth << "\n";
    if (dts[dt].possibilities.size() == 1) {
        dts[dt].d = dts[dt].possibilities[0];
        dts[dt].possibilities.clear();
        dts[dt].subdts[0] = -1;
        return ;
    }
    if (depth == 0) {
        return ;
    }
    if (dts[dt].d <= 0) {
        Dt **best_spl = NULL;
        int best_guess;
        double best_score = MAXL * 2;
        for (int i = 0; i < valid_guesses.size(); i++) {
            int guess = valid_guesses[i];
            Dt **curr_spl = split(dt, guess);
            double curr_score = score_spl(curr_spl);
            // cout << "using " << guess << " score is " << curr_score << "\n";
            if (curr_score < best_score) {
                if (best_spl != NULL) {
                    delete_spl(best_spl);
                }
                best_spl = curr_spl;
                best_score = curr_score;
                best_guess = guess;
            } else {
                delete_spl(curr_spl);
            }
        }
        assert (best_spl != NULL);
        // cout << dt << " best guess " << best_guess << ", with score " << best_score << "\n";
        alloc_spl(dt, best_spl);
        delete_spl(best_spl);
        dts[dt].possibilities.clear();
        dts[dt].d = best_guess;
    } else if (dts[dt].possibilities.size() > 0) {
        // repartition the possibilities
        Dt **best_spl = split(dt, dts[dt].d);
        for (int i = 0; i < MAXL + 1; i++) {
            if (dts[dt].subdts[i]) {
                assert(best_spl[i]->possibilities.size() > 0);
                dts[dts[dt].subdts[i]].possibilities = best_spl[i]->possibilities;
            }
        }
        delete_spl(best_spl);
    }
    for (int i = 0; i < MAXL + 1; i++) {
        // cout << dts[dt].subdts[i] << "\t";
        if (dts[dt].subdts[i] != 0) {
            find_guess(dts[dt].subdts[i], depth - 1);
        }
    }
    // cout << "\n";
}

// void random_sol (int dt, vector<pair<string, int>> &constraints) {
//     if (dts[dt].subdts[0] == -1) {
//         return ;
//     }
//     vector<int> ch;
//     for (int i = 0; i < MAXL + 1; i++) {
//         if (dts[dt].subdts[i]) {
//             ch.push_back(i);
//         }
//     }
//     random_shuffle(ch.begin(), ch.end());
//     cout << ch[0] << "\n";
//     constraints.push_back({ valid_guesses[dts[dt].d], ch[0] });
//     random_sol(dts[dt].subdts[ch[0]], constraints);
// }

// bool _solve (int i, string &curr, vector<pair<string, int>> &constraints) {
//     bool is_eq = true;
//     for (auto &c: constraints) {
//         int eq = find_eq(curr, c.first);
//         if (eq < c.second) {
//             return false;
//         } else if (eq != c.second) {
//             is_eq = false;
//         }
//     }
//     if (i == curr.size()) {
//         return is_eq;
//     }
//     string options = "BRG";
//     for (char nxt: options) {
//         curr[i] = nxt;
//         if (_solve(i + 1, curr, constraints)) {
//             return true;
//         }
//     }
//     curr[i] = 'G';
//     return false;
// }

// string solve_by_constraints (vector<pair<string, int>> &constraints) {
//     string curr(MAXL, 'G');
//     _solve(0, curr, constraints);
//     return curr;
// }

void print_dt () {
    cout << "\"{";
    for (int dt = 0; dt < dts.size(); dt++) {
        if (dt > 0) cout << ',';
        if ((dt + 1) % 90 == 0) cout << "\"\n\"";
        cout << '{';
        cout << dts[dt].d << ",{";
        int tot = 0;
        for (int i = 0; i < MAXL + 1; i++) {
            tot += dts[dt].subdts[i];
        }
        for (int i = 0; tot; tot -= dts[dt].subdts[i++]) {
            if (i > 0) cout << ',';
            cout << dts[dt].subdts[i];
        }
        cout << "}}";
    }
    cout << "}\"\n";
}

int main () {
    find_combs(MAXL);
    dts.push_back({ -1, { -1 } });
    dts.push_back({ -1, {}, all_combs });
    find_guess(1, (MAXL + 1) / 2);
    // print_dt();
    for (int i = 0; i < dts.size(); i++) {
        dts[i].possibilities.clear();
    }
    // dts[1].possibilities = all_combs;
    // find_guess(1, 0);
    print_dt();
    cout << score(dts[1]).first << "\n";
    cout << score(dts[1]).second << "\n";

    // srand(time(NULL));
    // vector<pair<string, int>> constraints;
    // random_sol(1, constraints);
    // for (auto i: constraints) {
    //     cout << i.first << " -> " << i.second << "\n";
    // }
    // cout << "found string is " << solve_by_constraints(constraints) << "\n";
}
