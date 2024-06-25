from typing import List


class Solution:
    def solve(self, left, right):
        if left > right:
            return 0

        if self.memo[left][right] is not None:
            return self.memo[left][right]

        res = 0
        for split in range(left, right + 1):
            curr = self.nums[left - 1] * self.nums[split] * self.nums[right + 1]
            curr += self.solve(left, split - 1)
            curr += self.solve(split + 1, right)
            if curr > res:
                res = curr

        self.memo[left][right] = res
        return res

    def maxCoins(self, nums: List[int]) -> int:
        self.nums = [1, *nums, 1]
        self.memo = [[None] * len(self.nums) for _ in self.nums]
        return self.solve(1, len(self.nums) - 2)
