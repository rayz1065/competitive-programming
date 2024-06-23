from typing import List


class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        res = []
        word_length = len(words[0])

        totals = {x: 0 for x in words}
        for word in words:
            totals[word] += 1

        for starting_i in range(word_length):
            frequencies = {x: 0 for x in words}
            missing = len(frequencies)

            for j, _ in enumerate(words):
                if starting_i + (j + 1) * word_length > len(s):
                    break

                word = s[
                    starting_i + j * word_length : starting_i + (j + 1) * word_length
                ]
                if word in frequencies:
                    frequencies[word] += 1
                    if frequencies[word] == totals[word]:
                        missing -= 1

            if missing == 0:
                res.append(starting_i)

            for j in range(len(words), len(s)):
                if starting_i + (j + 1) * word_length > len(s):
                    break

                old_word = s[
                    starting_i
                    + (j - len(words)) * word_length : starting_i
                    + (j + 1 - len(words)) * word_length
                ]
                if old_word in frequencies:
                    if frequencies[old_word] == totals[old_word]:
                        missing += 1
                    frequencies[old_word] -= 1

                word = s[
                    starting_i + j * word_length : starting_i + (j + 1) * word_length
                ]
                if word in frequencies:
                    frequencies[word] += 1
                    if frequencies[word] == totals[word]:
                        missing -= 1

                if missing == 0:
                    res.append(starting_i + (j - len(words) + 1) * word_length)

        return res
