#include <vector>

using namespace std;

int rimembra(int n, int k, vector<int> known) {
    int l = 0, r = 0, missing = 0;
    int best = 0;

    while (r < n) {
        if (missing > k) {
            missing -= 1 - known[l];
            l += 1;
        } else if (missing <= k) {
            missing += 1 - known[r];
            r += 1;
        }

        if (missing <= k) {
            best = max(best, r - l);
        }
    }

    return best;
}
