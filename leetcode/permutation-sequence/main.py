from itertools import permutations


class Solution:
    def getPermutation(self, n: int, k: int) -> str:
        res = list(permutations(range(1, n + 1)))[k - 1]

        return "".join(str(x) for x in res)
