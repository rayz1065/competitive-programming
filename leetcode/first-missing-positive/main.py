from typing import List


class Solution:
    def firstMissingPositive(self, nums: List[int]) -> int:
        for i, _ in enumerate(nums):
            while not (
                nums[i] <= 0 or nums[i] - 1 >= i or nums[i] == nums[nums[i] - 1]
            ):
                value = nums[i]
                nums[i], nums[value - 1] = nums[value - 1], nums[i]

        for i, value in enumerate(nums):
            if i + 1 != value:
                return i + 1

        return len(nums) + 1
