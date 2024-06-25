class Solution:
    def numberToWords(self, num: int) -> str:
        # fmt: off
        NUMBERS = [
            "Zero","One","Two","Three","Four","Five",
            "Six","Seven","Eight","Nine","Ten","Eleven",
            "Twelve","Thirteen","Fourteen","Fifteen",
            "Sixteen","Seventeen","Eighteen","Nineteen",
        ]
        TENS = [
            "0","1","Twenty","Thirty","Forty","Fifty",
            "Sixty","Seventy","Eighty","Ninety",
        ]
        POWERS = {
            2: "Hundred",
            3: "Thousand",
            6: "Million",
            9: "Billion",
        }
        # fmt: on

        if num < len(NUMBERS):
            return NUMBERS[num]

        res = []

        for exponent in [9, 6, 3, 2]:
            if num >= 10**exponent:
                partial = num // 10**exponent
                num = num % 10**exponent
                res.append(self.numberToWords(partial))
                res.append(POWERS[exponent])

        if num >= 20:
            tens = num // 10
            num = num % 10
            res.append(TENS[tens])

        if num > 0:
            res.append(NUMBERS[num])

        return " ".join(res)
