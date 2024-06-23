from functools import cache


class Solution:
    @cache
    def isMatch(self, s: str, p: str) -> bool:
        if len(s) == len(p) == 0:
            # done
            return True
        if len(p) == 0:
            return False

        if len(p) < 2 or p[1] != "*":
            # no klenee
            if len(s) == 0:
                return False

            if s[0] != p[0] and p[0] != ".":
                return False

            return self.isMatch(s[1:], p[1:])

        # klenee
        if self.isMatch(s, p[2:]):
            return True

        if len(s) == 0 or (s[0] != p[0] and p[0] != "."):
            return False

        return self.isMatch(s[1:], p)
