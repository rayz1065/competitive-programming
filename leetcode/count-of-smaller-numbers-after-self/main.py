from typing import List


class Solution:
    def add(self, index, value):
        index += 1
        while index < len(self.fenwick):
            self.fenwick[index] += value
            index += index & (-index)

    def sum(self, index):
        index += 1
        res = 0
        while index > 0:
            res += self.fenwick[index]
            index -= index & (-index)

        return res

    def range_sum(self, a, b):
        if a == 0:
            return self.sum(b)
        return self.sum(b) - self.sum(a - 1)

    def countSmaller(self, nums: List[int]) -> List[int]:
        self.fenwick = [0] * (2 * 10**4 + 5)

        res = []
        for i, num in enumerate(reversed(nums)):
            num += 10**4
            self.add(num, 1)
            res.append(self.range_sum(0, num - 1))

        return list(reversed(res))
