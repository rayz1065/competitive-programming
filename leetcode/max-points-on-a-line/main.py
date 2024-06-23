from math import sqrt
from typing import List


class Solution:
    def normalize(self, vec):
        amp = sqrt(sum(x**2 for x in vec))

        if amp == 0:
            return vec

        vec = [x / amp for x in vec]

        if vec[0] < 0:
            vec = [-x for x in vec]

        return vec

    def same(self, vec1, vec2):
        return all(abs(x - y) < 1e-8 for x, y in zip(vec1, vec2))

    def find_in_line(self, points, a, b):
        ab = self.vectors[a][b]

        res = 0
        for c, _ in enumerate(points):
            if a == c:
                res += 1
                continue

            ac = self.vectors[a][c]
            if self.same(ab, ac):
                res += 1

        return res

    def maxPoints(self, points: List[List[int]]) -> int:
        best = 1

        self.vectors = [
            [self.normalize([x[i] - y[i] for i, _ in enumerate(x)]) for y in points]
            for x in points
        ]

        for a, _ in enumerate(points):
            for b, _ in enumerate(points):
                if b <= a:
                    continue

                best = max(best, self.find_in_line(points, a, b))

        return best
