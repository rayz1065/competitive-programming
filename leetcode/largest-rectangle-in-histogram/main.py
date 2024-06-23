from typing import List


class Solution:
    def largestRectangleArea(self, heights: List[int]) -> int:
        # (idx, height)
        stack = [(0, 0)]
        best = 0
        for idx, height in enumerate(heights):
            first_idx = idx
            while stack[-1][1] > height:
                first_idx = stack[-1][0]
                best = max(best, (idx - first_idx) * stack[-1][1])
                stack.pop()
            if stack[-1][1] < height:
                stack.append((first_idx, height))

        for idx, height in stack:
            best = max(best, (len(heights) - idx) * height)

        return best
