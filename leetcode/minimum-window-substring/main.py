class Solution:
    def minWindow(self, s: str, t: str) -> str:
        targets = {x: 0 for x in t}
        for letter in t:
            targets[letter] += 1

        frequencies = {x: 0 for x in s}
        missing = len(t)
        i, j = 0, 0

        best = None
        best_ij = None

        while True:
            if missing > 0:
                # advance j
                if j == len(s):
                    break

                if s[j] in targets and frequencies[s[j]] < targets[s[j]]:
                    missing -= 1

                frequencies[s[j]] += 1
                j += 1
            else:
                # advance i
                if s[i] in targets and frequencies[s[i]] == targets[s[i]]:
                    missing += 1

                frequencies[s[i]] -= 1
                i += 1

            if missing == 0 and (best is None or best > j - i):
                best = j - i
                best_ij = (i, j)

        if best_ij is None:
            return ""

        i, j = best_ij
        return s[i:j]
