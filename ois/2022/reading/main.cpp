#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>
#pragma GCC optimize("O3")

using namespace std;

// input data
int n_papers, l_days;
pair<int, int> papers[150005];

int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> n_papers >> l_days;
    for (int i = 0; i < n_papers; i++) {
        cin >> papers[i].second >> papers[i].first;
    }
    sort(papers, papers + n_papers);

    multiset<int> available;
    int next_paper = n_papers - 1;
    for (int i = 0; i < n_papers && papers[i].first == -1; i++) {
        available.insert(-papers[i].second);
    }

    int s = 0;
    for (int day = l_days - 1; day >= 0; day--) {
        // add available papers
        while (next_paper >= 0 && papers[next_paper].first >= day) {
            // will automatically skip -1
            // cout << "at day " << day << " adding " << next_paper << " with pages " << papers[next_paper].second << "\n";
            available.insert(-papers[next_paper].second);
            next_paper--;
        }
        // read something
        auto read = available.begin();
        if (read != available.end()) {
            s += -*read;
            available.erase(read);
        }
    }

    cout << s << endl; // print the result
    return 0;
}
