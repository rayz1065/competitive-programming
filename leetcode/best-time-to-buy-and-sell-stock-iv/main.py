from typing import List
from functools import cache


class Solution:

    @cache
    def solve(self, i, k):
        if k == 0 or i == len(self.prices):
            return 0

        res = self.solve(i + 1, k)
        best_instant = 0
        for j in range(i + 1, len(self.prices)):
            if self.prices[j] - self.prices[i] > best_instant:
                best_instant = self.prices[j] - self.prices[i]
                res = max(res, best_instant + self.solve(j, k - 1))

        return res

    def maxProfit(self, k: int, prices: List[int]) -> int:
        self.prices = prices

        return self.solve(0, k)
