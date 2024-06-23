#include <bits/stdc++.h>

using namespace std;

class Solution {
   public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff,
                                       int valueDiff) {
        multiset<int> values;

        for (int i = 0; i < nums.size(); i++) {
            if (i > indexDiff) {
                values.erase(values.find(nums[i - indexDiff - 1]));
            }

            auto res = values.upper_bound(nums[i]);
            if (res != values.end() && abs(nums[i] - *res) <= valueDiff) {
                return true;
            }

            if (res != values.begin()) {
                res--;
                if (abs(nums[i] - *res) <= valueDiff) {
                    return true;
                }
            }

            values.insert(nums[i]);
        }

        return false;
    }
};
