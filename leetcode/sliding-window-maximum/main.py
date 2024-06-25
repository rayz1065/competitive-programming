from typing import List


class Solution:
    def maxSlidingWindow(self, nums: List[int], k: int) -> List[int]:
        stack = []
        for i in range(k):
            while stack and nums[i] > stack[-1][0]:
                stack.pop()
            stack.append((nums[i], i))

        res = []
        stack_first_idx = 0
        for i in range(k, len(nums)):
            res.append(stack[stack_first_idx][0])
            while len(stack) > stack_first_idx and nums[i] > stack[-1][0]:
                stack.pop()

            stack.append((nums[i], i))

            while stack[stack_first_idx][1] <= i - k:
                stack_first_idx += 1

        res.append(stack[stack_first_idx][0])

        return res
