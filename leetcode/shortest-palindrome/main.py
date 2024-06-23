class Solution:
    def shortestPalindrome(self, s: str) -> str:
        end_hash = 0
        prefix = ""
        prefix_hash = 0
        start_hash = 0
        start_hash_memo = []

        MOD = 100000007

        for i, chr_ in enumerate(reversed(s)):
            end_hash = (end_hash * 26 + ord(chr_) - ord("a")) % MOD
            start_hash_memo.append(start_hash)
            start_hash = start_hash * 26 + ord(s[i - len(prefix)]) - ord("a")

            while (
                prefix_hash * pow(26, i + 1 - len(prefix), MOD) + start_hash
            ) % MOD != end_hash:
                # copy the first un-copied letter to the prefix
                prefix_chr = s[len(s) - 1 - len(prefix)]
                prefix += prefix_chr
                prefix_hash = prefix_hash * 26 + ord(prefix_chr) - ord("a")

                start_hash = start_hash_memo[-1]
                start_hash_memo.pop()

        return prefix + s
