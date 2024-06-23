from functools import cache


class Solution:
    @cache
    def solve(self, i, j):
        if j == len(self.t):
            return 1
        elif i == len(self.s):
            return 0

        res = self.solve(i + 1, j)

        if self.s[i] == self.t[j]:
            res += self.solve(i + 1, j + 1)

        return res

    def numDistinct(self, s: str, t: str) -> int:
        self.s = s
        self.t = t

        return self.solve(0, 0)
