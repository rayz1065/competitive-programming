from functools import cache


class Solution:

    @cache
    def solve(self, i1, j1, i2, j2):
        if i1 == j1:
            return self.s1[i1] == self.s2[i2]

        for k in range(j1 - i1):
            # [i1, i1 + k], [i1 + k + 1, j1]
            # same order
            if self.solve(i1, i1 + k, i2, i2 + k) and self.solve(
                i1 + k + 1, j1, i2 + k + 1, j2
            ):
                return True

            # swapped
            k1 = j1 - i1 - k - 1
            if self.solve(i1 + k1 + 1, j1, i2, i2 + k) and self.solve(
                i1, i1 + k1, i2 + k + 1, j2
            ):
                return True

        return False

    def isScramble(self, s1: str, s2: str) -> bool:
        self.s1 = s1
        self.s2 = s2

        return self.solve(0, len(s1) - 1, 0, len(s2) - 1)
