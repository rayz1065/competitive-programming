class Solution:
    def longestValidParentheses(self, s: str) -> int:
        # stack[i] = (starting index, is closed)
        stack = [[-1, 0]]
        best = 0

        for i, par in enumerate(s):
            if par == "(":
                if stack[-1][1]:
                    stack[-1][1] = 0
                else:
                    stack.append([i, 0])
            else:
                if stack[-1][1]:
                    stack.pop()

                if len(stack) > 1:
                    stack[-1][1] = 1
                    best = max(best, i - stack[-1][0] + 1)
                else:
                    stack[-1][0] = i

        return best
