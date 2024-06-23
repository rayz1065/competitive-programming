from functools import lru_cache, cache


class Solution:

    @lru_cache(maxsize=10000)
    def _is_palindrome(self, s):
        for k in range(len(s) // 2):
            if s[k] != s[-1 - k]:
                return False

        return True

    def is_palindrome(self, i, j):
        s = self.s
        return self._is_palindrome(s[i : j + 1])

    @cache
    def solve(self, i, j) -> int:
        s = self.s
        if self.is_palindrome(i, j):
            return 0

        best = j - i
        for k in range(0, j - i):
            if self.is_palindrome(i, i + k):
                best = min(best, self.solve(i + k + 1, j) + 1)

        return best

    def minCut(self, s: str) -> int:
        self.s = s

        return self.solve(0, len(s) - 1)
