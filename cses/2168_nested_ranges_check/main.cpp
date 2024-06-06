#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
pair<int, int> ranges_[MAXN];
pair<int, int> range_starts[MAXN], range_ends[MAXN];

bool contained[MAXN];
bool found_contents[MAXN];

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> ranges_[i].first >> ranges_[i].second;
        range_starts[i] = {ranges_[i].first, i};
        range_ends[i] = {ranges_[i].second, i};
    }

    sort(range_starts, range_starts + n);
    sort(range_ends, range_ends + n);

    range_starts[n] = {INT_MAX >> 1, -1};
    range_ends[n] = {INT_MAX >> 1, -1};

    set<pair<int, int>> open_ranges;
    set<pair<int, int>> looking_for_contents;

    int trash_time = -1;
    set<pair<int, int>> trash;

    int current_time = -1;

    for (int start_i = 0, end_j = 0; start_i < n || end_j < n;) {
        if (range_starts[start_i].first < range_ends[end_j].first) {
            current_time = range_starts[start_i].first;
            open_ranges.insert(range_starts[start_i]);
            looking_for_contents.insert(range_starts[start_i]);
            start_i += 1;
        } else {
            int range_idx = range_ends[end_j].second;
            int start_time = ranges_[range_idx].first;
            current_time = ranges_[range_idx].second;

            if (trash_time < current_time) {
                trash_time = current_time;
                for (auto x : trash) {
                    open_ranges.erase(x);
                    looking_for_contents.erase(x);
                }
                trash.clear();
            }

            trash.insert({start_time, range_idx});
            open_ranges.erase({start_time, range_idx});
            looking_for_contents.erase({start_time, range_idx});

            // look for a range that started before start_time
            // and that is still open
            auto it = open_ranges.upper_bound({start_time, n});
            if (it != open_ranges.begin()) {
                it--;
                contained[range_idx] = true;
            }

            // look for all the ranges that started before start_time
            // and have not found content
            auto it2 = looking_for_contents.upper_bound({start_time, n});
            auto next_ = it2;
            if (next_ != looking_for_contents.begin()) {
                next_--;
            }

            bool done = it2 == looking_for_contents.begin();

            while (!done) {
                it2 = next_;
                if (next_ != looking_for_contents.begin()) {
                    next_--;
                } else {
                    done = true;
                }

                found_contents[it2->second] = true;
                looking_for_contents.erase(it2);
            }

            end_j += 1;

            open_ranges.insert({start_time, range_idx});
            if (!found_contents[range_idx]) {
                looking_for_contents.insert({start_time, range_idx});
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << found_contents[i] << " \n"[i + 1 == n];
    }
    for (int i = 0; i < n; i++) {
        cout << contained[i] << " \n"[i + 1 == n];
    }
}
