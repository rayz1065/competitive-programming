from typing import List


class Solution:

    def solve(self, i):
        ratings = self.ratings
        res = 1

        if self.solutions[i] is not None:
            return self.solutions[i]

        if i > 0 and ratings[i] > ratings[i - 1]:
            res = max(res, self.solve(i - 1) + 1)
        if i + 1 < len(ratings) and ratings[i] > ratings[i + 1]:
            res = max(res, self.solve(i + 1) + 1)

        self.solutions[i] = res

        return res

    def candy(self, ratings: List[int]) -> int:
        self.ratings = ratings
        self.solutions = [None] * len(ratings)

        return sum(self.solve(i) for i, _ in enumerate(ratings))
