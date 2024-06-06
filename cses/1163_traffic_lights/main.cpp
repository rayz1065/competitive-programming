#include <bits/stdc++.h>
#define MAXN 200005

using namespace std;

int n;
int streetlights[MAXN];

inline int segment_length(pair<int, int> segment) {
    return segment.second - segment.first;
}

int main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int street_length;
    cin >> street_length >> n;

    for (int i = 0; i < n; i++) {
        cin >> streetlights[i];
    }

    set<pair<int, int>> segments;
    multiset<int> longest_segments;

    segments.insert({0, street_length});
    longest_segments.insert(-segment_length(*segments.begin()));

    for (int i = 0; i < n; i++) {
        auto it = segments.upper_bound({streetlights[i], streetlights[i]});
        it--;  // there must be one before

        pair<int, int> segment = *it;
        segments.erase(it);
        longest_segments.erase(longest_segments.find(-segment_length(segment)));

        pair<int, int> a = {segment.first, streetlights[i]},
                       b = {streetlights[i], segment.second};
        segments.insert(a);
        segments.insert(b);
        longest_segments.insert(-segment_length(a));
        longest_segments.insert(-segment_length(b));

        cout << (-*longest_segments.begin()) << " \n"[i + 1 == n];
    }
}
