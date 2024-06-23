from typing import List


class Solution:
    def trap(self, heights: List[int]) -> int:
        left_heights = [0]
        for height in heights:
            left_heights.append(max(left_heights[-1], height))

        right_heights = [0]
        for height in reversed(heights):
            right_heights.append(max(right_heights[-1], height))

        right_heights = list(reversed(right_heights))

        res = []

        for left, height, right in zip(left_heights[1:], heights, right_heights[:-1]):
            res.append(abs(height - min(left, right)))

        return sum(res)
