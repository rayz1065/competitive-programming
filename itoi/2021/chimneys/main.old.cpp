#include <bits/stdc++.h>
#define MAXN 10005
#define MAXA 100005

using namespace std;

typedef long long ll;
chrono::_V2::system_clock::time_point start_time;

void set_timer () {
    start_time = chrono::high_resolution_clock::now();
}

bool is_timeout () {
    auto elapsed = chrono::high_resolution_clock::now() - start_time;
    ll milliseconds = chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
    return milliseconds > 9750;
}

struct Segment {
    int id;
    int a_sm;
    int b_lg;
    int len;
};
typedef vector<Segment> Chimney;

int n;
Segment segments[MAXN];
ll best_score;
vector<Chimney> best;
vector<Chimney> curr;
vector<int> segments_starting_at[MAXA];
bool used[MAXN];
int start_freq[MAXA];

int next_segment[MAXN];
int prev_segment[MAXN];

ll chimney_length (Chimney &chimney) {
    ll s = 0;
    for (auto i: chimney) {
        s += i.len;
    }
    return s;
}

ll shortest_chimney () {
    ll score = INT_MAX >> 1;
    for (auto &i: curr) {
        score = min(score, chimney_length(i));
    }
    return score;
}

bool sort_by_len (Chimney &a, Chimney &b) {
    return chimney_length(a) < chimney_length(b);
}

bool can_append (Chimney &base, Chimney &x) {
    if (base.empty() || x.empty()) {
        return true;
    }
    Segment base_last = base[base.size() - 1];
    Segment x_first = x[0];
    return base_last.b_lg == x_first.a_sm;
}

bool can_combine (Chimney &a, Chimney &b) {
    return can_append(a, b) || can_append(b, a);
}

Chimney combine (Chimney &a, Chimney &b) {
    if (!can_append(a, b)) {
        swap(a, b);
    }
    assert(can_append(a, b));
    auto res = a;
    for (auto x: b) {
        res.push_back(x);
    }
    return res;
}

pair<Chimney, Chimney> slice_chimney (Chimney &a, int mid) {
    Chimney beg, end;
    for (int i = 0; i < a.size(); i++) {
        if (i < mid) {
            beg.push_back(a[i]);
        } else {
            end.push_back(a[i]);
        }
    }
    return { beg, end };
}

// void print_chimney (Chimney c) {
//     for (auto i: c) {
//         cerr << i.id << " ";
//     }
// }

pair<ll, pair<Chimney, Chimney>> most_even_intersect (Chimney &a, Chimney &b) {
    assert(!can_combine(a, b));
    ll curr = min(chimney_length(a), chimney_length(b));
    pair<Chimney, Chimney> best = { a, b };
    ll s = curr; // -1 for impossible
    // cerr << a[0].id << " " << b[0].id << "\n";
    for (int i = 0; i <= a.size(); i++) {
        for (int j = 0; j <= b.size(); j++) {
            // new chimneys [a.start, b.end], [b.start, a.end]
            auto sliced_a = slice_chimney(a, i);
            auto sliced_b = slice_chimney(b, j);
            // cerr << "a: ", print_chimney(sliced_a.first), cerr << " / ", print_chimney(sliced_a.second), cerr << "\n";
            // cerr << "b: ", print_chimney(sliced_b.first), cerr << " / ", print_chimney(sliced_b.second), cerr << "\n";
            if(!can_append(sliced_a.first, sliced_b.second) || !can_append(sliced_b.first, sliced_a.second)) {
                continue ;
            }
            auto res1 = combine(sliced_a.first, sliced_b.second);
            auto res2 = combine(sliced_b.first, sliced_a.second);
            ll new_split = min(chimney_length(res1), chimney_length(res2));
            if (new_split > s) {
                s = new_split;
                best = { res1, res2 };
            }
        }
    }
    if (s <= curr) {
        s = -1;
    } else {
        // cerr << "even split: " << s << " vs " << chimney_length(a) << "," << chimney_length(b) << "\n";
    }
    return { s, best };
}

void scramble () {
    int initial_size = curr.size();
    for (int i = 0; i < initial_size; i++) {
        if (((double) rand() / RAND_MAX) < .1) {
            int j = rand() % curr[i].size() + 1;
            auto res = slice_chimney(curr[i], j);
            if (!res.second.empty()) {
                curr[i] = res.first;
                curr.push_back(res.second);
            }
        }
    }
}

int optimize () {
    int found = 0;
    sort(curr.begin(), curr.end(), sort_by_len);
    ll shortest_len = chimney_length(curr[0]);
    for (int i = 0; i < curr.size(); i++) {
        if (chimney_length(curr[i]) > shortest_len) {
            break ;
        }
        for (int j = i + 1; j < curr.size() && !is_timeout(); j++) {
            if (can_combine(curr[i], curr[j])) {
                auto res = combine(curr[i], curr[j]);
                curr[i] = res;
                curr.erase(curr.begin() + j);
                found += 1;
                break ;
            }
            auto inters = most_even_intersect(curr[i], curr[j]);
            if (inters.first != -1) {
                curr[i] = inters.second.first;
                curr[j] = inters.second.second;
                found += 1;
                break ;
            }
        }
    }
    ll score = shortest_chimney();
    if (score > best_score) {
        best = curr;
        best_score = score;
    }
    return found;
}

void print_best () {
    cerr << "score: " << best_score << "\n";
    cout << best.size() << "\n";
    for (auto &chimney: best) {
        cout << chimney.size() << "\n";
        for (auto j: chimney) {
            cout << j.id << " ";
        }
        cout << "\n";
    }
}

void visit_deep (int node) {
    // appends to curr
    Chimney chimney;
    while (true) {
        used[node] = true;
        chimney.push_back(segments[node]);
        int next = -1;
        for (auto j: segments_starting_at[segments[node].b_lg]) {
            if (!used[j]) {
                next = j;
                break ;
            }
        }
        if (next == -1) {
            break ;
        }
        node = next;
    }
    curr.push_back(chimney);
}

void greedy_solution () {
    for (int i = 0; i < MAXA; i++) {
        for (auto j: segments_starting_at[i]) {
            if (used[j]) {
                continue ;
            }
            visit_deep(j);
        }
    }
}

int main () {
    set_timer();
    srand(1065);
    cin >> n;
    bool has_duplicates = false;
    for (int i = 0; i < n; i++) {
        segments[i].id = i;
        cin >> segments[i].a_sm >> segments[i].b_lg >> segments[i].len;
        segments_starting_at[segments[i].a_sm].push_back(i);
        if (segments_starting_at[segments[i].a_sm].size() > 1) {
            has_duplicates = true;
        }
        start_freq[segments[i].b_lg] += 1;
        if (start_freq[segments[i].b_lg] > 1) {
            has_duplicates = true;
        }
    }
    greedy_solution();
    best = curr;
    best_score = shortest_chimney();

    if (!has_duplicates) {
        cerr << "no duplicates\n";
        print_best();
        return 0;
    }
    // while (optimize());
    // curr.clear();
    // for (int i = 0; i < n; i++) {
    //     curr.push_back({ segments[i] });
    // }

    while (!is_timeout()) {
        while (optimize());
        scramble();
    }

    print_best();
}
