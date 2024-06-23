from typing import List


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        value_one = 10**5 + 5
        profit_one = 0
        best = 0

        highest_selling = [0]
        for price in reversed(prices):
            highest_selling.append(max(price, highest_selling[-1]))
        highest_selling = list(reversed(highest_selling))

        for idx, price in enumerate(prices):
            # try buying one
            value_one = min(value_one, price)

            # try buying two
            best = max(best, max(0, highest_selling[idx + 1] - price) + profit_one)

            # try selling one
            profit_one = max(profit_one, abs(price - value_one))

        return best
