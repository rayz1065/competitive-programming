from typing import List


class Solution:
    def solve(self, s, i, curr, depth):
        if len(curr) + len(s) - i < self.solution_len or depth > len(s) - i:
            return

        if i == len(s):
            if len(curr) > self.solution_len:
                self.solutions = set()
                self.solution_len = len(curr)

            self.solutions.add(curr)
            return

        nxt = curr + s[i]
        if s[i] == "(":
            self.solve(s, i + 1, nxt, depth + 1)
        elif s[i] == ")" and depth > 0:
            self.solve(s, i + 1, nxt, depth - 1)
        elif s[i] not in "()":
            self.solve(s, i + 1, nxt, depth)

        if s[i] in "()":
            self.solve(s, i + 1, curr, depth)

    def removeInvalidParentheses(self, s: str) -> List[str]:
        self.solutions = set()
        self.solution_len = 0
        self.solve(s, 0, "", 0)

        return list(self.solutions)
