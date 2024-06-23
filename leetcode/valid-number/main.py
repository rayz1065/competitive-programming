import re


class Solution:
    def isNumber(self, s: str) -> bool:
        patterns = [
            re.compile(r"^[-+]?\d+(?:[eE][-+]?\d+)?$"),
            re.compile(r"^[-+]?(?:\d+\.\d*|\.\d+)(?:[eE][-+]?\d+)?$"),
        ]

        return any(pat.match(s) is not None for pat in patterns)
