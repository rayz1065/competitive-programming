from typing import List


class Solution:
    def find_neighbors(self, a):
        for i in range(len(a)):
            for chr_ in range(26):
                b = list(a)
                b[i] = chr(ord("a") + chr_)

                b = "".join(b)
                if b != a:
                    yield b

    def ladderLength(self, beginWord: str, endWord: str, wordList: List[str]) -> int:
        distances = {beginWord: 0}

        wordList = set(wordList)
        wordList.add(beginWord)

        graph = {x: [] for x in wordList}
        for word in wordList:
            for other in self.find_neighbors(word):
                if other not in wordList:
                    continue

                graph[word].append(other)

        ff = [beginWord]
        while ff:
            word = ff[0]
            ff = ff[1:]  # slow

            for other in graph[word]:
                if other not in distances:
                    distances[other] = distances[word] + 1
                    ff.append(other)

        if endWord not in distances:
            return 0

        return distances[endWord] + 1
