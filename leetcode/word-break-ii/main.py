from typing import List


class Solution:
    def wordBreak(self, s: str, wordDict: List[str]) -> List[str]:
        res = []

        for word in wordDict:
            if s == word:
                res.append(s)
                continue
            if not s.startswith(word):
                continue

            child = self.wordBreak(s[len(word) :], wordDict)
            for x in child:
                res.append(f"{word} {x}")

        return res
