from functools import cache


class Solution:

    @cache
    def solve(self, i, j):
        s = self.s
        p = self.p
        if i == len(s) and j == len(p):
            return True
        if j == len(p):
            return False

        if i < len(s) and (s[i] == p[j] or p[j] == "?"):
            # first character matches (no *)
            return self.solve(i + 1, j + 1)

        if p[j] != "*":
            # first character mismatches (no *)
            return False

        for new_i in range(i, len(s) + 1):
            if self.solve(new_i, j + 1):
                return True

        return False

    def isMatch(self, s: str, p: str) -> bool:
        self.s = s
        self.p = p

        return self.solve(0, 0)
