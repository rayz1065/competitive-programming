class Solution:
    def compute(self, operations):
        res = 0
        if isinstance(operations[0], int):
            operations = ["+", *operations]

        for i in range(0, len(operations), 2):
            if operations[i] == "+":
                res += operations[i + 1]
            elif operations[i] == "-":
                res -= operations[i + 1]
            else:
                raise ValueError(f"Unknown operations {operations[i]}")

        return res

    def calculate(self, s: str) -> int:
        s = s.replace(" ", "")

        tokens = []
        for chr_ in s:
            if chr_.isdigit():
                if tokens and isinstance(tokens[-1], int):
                    tokens[-1] = tokens[-1] * 10 + int(chr_)
                else:
                    tokens.append(int(chr_))
            else:
                tokens.append(chr_)

        stack = [[]]
        for token in tokens:
            if token == "(":
                stack.append([])
            elif token == ")":
                res = self.compute(stack[-1])
                stack.pop()
                stack[-1].append(res)
            else:
                stack[-1].append(token)

        return self.compute(stack[-1])
