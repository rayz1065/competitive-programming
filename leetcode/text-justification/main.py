from typing import List


class Solution:
    def fullJustify(self, words: List[str], maxWidth: int) -> List[str]:
        lines = [[]]
        last_line_len = 0

        for word in words:
            if last_line_len + len(word) + len(lines[-1]) > maxWidth:
                lines.append([])
                last_line_len = 0
            lines[-1].append(word)
            last_line_len += len(word)

        # last must be left-justified
        lines[-1] = [" ".join(lines[-1])]

        res = []
        for line in lines:
            spaces = maxWidth - sum(len(x) for x in line)

            if len(line) == 1:
                line.append("")

            gaps = len(line) - 1
            div = spaces // gaps
            rest = spaces % gaps

            line_res = []
            for i, word in enumerate(line):
                line_res.append(word)
                if i + 1 < len(line):
                    line_res.append(" " * div)
                if i + 1 <= rest:
                    line_res.append(" ")

            res.append("".join(line_res))

        return res
