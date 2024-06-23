from typing import List


class Solution:
    def get_distance(self, a, b):
        if len(a) != len(b):
            return 9999

        return sum(int(x != y) for x, y in zip(a, b))

    def findLadders(
        self, beginWord: str, endWord: str, wordList: List[str]
    ) -> List[List[str]]:
        distances = {beginWord: 0}
        parents = {beginWord: []}
        ff = [beginWord]

        while ff:
            word = ff[0]
            ff = ff[1:]  # slow

            for other in wordList:
                if self.get_distance(word, other) != 1:
                    continue

                if other not in distances:
                    parents[other] = [word]
                    distances[other] = distances[word] + 1
                    ff.append(other)
                elif distances[other] == distances[word] + 1:
                    parents[other].append(word)

        if endWord not in distances:
            return []

        ff = [(endWord,)]
        res = []

        while ff:
            current = ff[-1]
            ff.pop()
            word = current[0]

            if word == beginWord:
                res.append(current)
                continue

            for other in parents[word]:
                ff.append((other, *current))

        return [list(x) for x in res]
