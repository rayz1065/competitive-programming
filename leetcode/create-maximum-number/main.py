from typing import List


class Solution:
    def maxNumber(self, nums1: List[int], nums2: List[int], k: int) -> List[int]:
        states = [(0, 0)]
        number = []

        while len(number) < k:
            next_states = []
            best_digit = -1
            missing_digits = k - len(number)

            for i, j in states:
                free_digits = len(nums1) - i + len(nums2) - j
                available_skips = free_digits - missing_digits

                found_i = False
                found_j = False

                for skip_i in range(0, min(available_skips + 1, len(nums1) - i)):
                    if nums1[i + skip_i] > best_digit:
                        best_digit = nums1[i + skip_i]
                        next_states = [(i + skip_i + 1, j)]
                    elif not found_i and nums1[i + skip_i] >= best_digit:
                        next_states.append((i + skip_i + 1, j))
                        found_i = True

                for skip_j in range(0, min(available_skips + 1, len(nums2) - j)):
                    if nums2[j + skip_j] > best_digit:
                        best_digit = nums2[j + skip_j]
                        next_states = [(i, j + skip_j + 1)]
                    elif not found_j and nums2[j + skip_j] >= best_digit:
                        next_states.append((i, j + skip_j + 1))
                        found_j = True

            states = set(next_states)
            number.append(best_digit)
        return number
