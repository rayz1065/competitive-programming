class Solution:
    def countDigitOne(self, n: int) -> int:
        res = 0

        while n > 0 and n % 10 != 9:
            res += len(str(n)) - len(str(n).replace("1", ""))
            n -= 1

        if n == 0:
            return res

        n //= 10
        return res + (n + 1) + 10 * self.countDigitOne(n)
