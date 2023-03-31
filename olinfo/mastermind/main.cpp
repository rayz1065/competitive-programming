#include <bits/stdc++.h>
#pragma GCC optimize("O3")
#define MAXN 20005

using namespace std;

struct PyDt {
    int d;
    int subdts[15];
    vector<int> possibilities;
};
vector<PyDt> dts;

// add dt string here
const char* dts_str = "";

typedef enum {BLACK, RED, GREEN} color_t;
void solution (color_t combination[]);
int examine (color_t combination[]);

int n;
int MAXL;
color_t curr[MAXN];
vector<int> all_combs;
vector<int> valid_guesses;

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

double score_spl (PyDt **spl) {
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

void fill_curr (int l, int r, color_t color) {
    // [l, r] inclusive
    fill(curr + l, curr + r + 1, color);
}

PyDt** split (int dt, int guess) {
    PyDt** subs = new PyDt*[MAXL + 1]();
    for (int i = 0; i < MAXL + 1; i++) {
        subs[i] = new PyDt();
        subs[i]->d = -1;
    }
    for (auto comb: dts[dt].possibilities) {
        int eq = find_eq(comb, guess);
        subs[eq]->possibilities.push_back(comb);
    }
    return subs;
}

void alloc_spl (int dt, PyDt** subs) {
    for (int i = 0; i < MAXL + 1; i++) {
        dts[dt].subdts[i] = 0;
        if (subs[i]->possibilities.size() > 0) {
            // allocate new DT
            dts.push_back(*(subs[i]));
            dts[dt].subdts[i] = dts.size() - 1;
        }
    }
}

void delete_spl (PyDt **spl) {
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
        PyDt **best_spl = NULL;
        int best_guess;
        double best_score = MAXL * 2;
        for (int i = 0; i < valid_guesses.size(); i++) {
            int guess = valid_guesses[i];
            PyDt **curr_spl = split(dt, guess);
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
        PyDt **best_spl = split(dt, dts[dt].d);
        for (int i = 0; i < MAXL + 1; i++) {
            if (dts[dt].subdts[i]) {
                assert(best_spl[i]->possibilities.size() > 0);
                dts[dts[dt].subdts[i]].possibilities = best_spl[i]->possibilities;
            }
        }
        delete_spl(best_spl);
        dts[dt].possibilities.clear();
    } else {
        return ;
    }
    for (int i = 0; i < MAXL + 1; i++) {
        // cout << dts[dt].subdts[i] << "\t";
        if (dts[dt].subdts[i] != 0) {
            find_guess(dts[dt].subdts[i], depth - 1);
        }
    }
    // cout << "\n";
}

color_t gchr_to_c (char c) {
    switch (c) {
        case 'R':
            return RED;
        case 'G':
            return GREEN;
        case 'B':
            return BLACK;
        default:
            assert(false);
    }
}

char c_to_gchr (color_t c) {
    switch (c) {
        case RED:
            return 'R';
        case GREEN:
            return 'G';
        case BLACK:
            return 'B';
        default:
            assert(false);
    }
}

void set_range (int l, int r, string guess) {
    for (int i = 0; i < r - l + 1; i++) {
        curr[l + i] = gchr_to_c(guess[i]);
    }
}

string int_to_str (int d) {
    string s;
    char conv[] = {'Z', 'B', 'R', 'G'};
    for (; d; d >>= 2) {
        assert(d&3);
        s += conv[d&3];
    }
    reverse(s.begin(), s.end());
    return s;
}

void solve_dts (int l, int r) {
    int dt = 1;
    // cout << "solving " << l << " -> " << r << "\n";
    while (dts[dt].subdts[0] != -1) {
        // try guessing the current one
        find_guess(dt, 1);
        set_range(l, r, int_to_str(dts[dt].d));
        int res = examine(curr);
        res = res - n + (r - l + 1);
        // cout << "guessed " << dts[dt].d << " res is " << res << "\n";
        dt = dts[dt].subdts[res];
        assert(dt != 0);
        // for (int i = 0; i <= r; i++) {
        //     cout << c_to_gchr(curr[i]);
        // }
        // cout << "\n";
    }
    set_range(l, r, int_to_str(dts[dt].d));
}

void construct_dts () {
    int dt = 0;
    int nesting = 0;
    int curr = 0;
    int sign = 1;
    int subdt_idx = 0;
    for (int i = 0; dts_str[i] != '\0'; i++) {
        if (dts_str[i] == '{') {
            nesting++;
            curr = 0;
            sign = 1;
            if (nesting == 2) {
                dts.push_back({});
            }
        }
        else if (dts_str[i] == '}') {
            if (nesting == 3) {
                // closing subdts
                dts[dt].subdts[subdt_idx] = sign * curr;
                subdt_idx = 0;
            } else if (nesting == 2) {
                // closing dt
                dt++;
            }
            nesting--;
        }
        else if (dts_str[i] == ',') {
            if (nesting == 2) {
                // just read decision
                dts[dt].d = sign * curr;
            } else if (nesting == 3) {
                // subdt
                dts[dt].subdts[subdt_idx++] = sign * curr;
            }
            curr = 0;
            sign = 1;
        }
        else if (dts_str[i] == '-') sign = -1;
        else if ('0' <= dts_str[i] && dts_str[i] <= '9') curr = curr * 10 + dts_str[i] - '0';
        else cout << "unknown character " << dts_str[i] << "\n";
    }
}

void find_secret (int n, int problem_type) {
    ::n = n;
    construct_dts();
    MAXL = int_to_str(dts[1].d).size();
    find_combs(MAXL);
    dts[1].possibilities = all_combs;
    fill_curr(0, n - 1, GREEN);
    for (int l = 0; l < n; l += MAXL) {
        if (l + MAXL >= n) l = n - MAXL;
        int r = l + MAXL - 1;
        solve_dts(l, r);
        // for (int i = 0; i <= r; i++) {
        //     cout << c_to_gchr(curr[i]);
        // }
    }
    solution(curr);
    return ;
}
