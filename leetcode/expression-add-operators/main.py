from typing import List
from itertools import product


class Solution:
    def has_leading_zeros(self, operation):
        number = ""
        for op in operation:
            if op.isdigit():
                number += op
                if number.startswith("0") and len(number) > 1:
                    return True
            else:
                number = ""

        return False

    def eval(self, operation):
        tokens = []
        for op in operation:
            if op.isdigit():
                if tokens and isinstance(tokens[-1], int):
                    tokens[-1] = tokens[-1] * 10 + int(op)
                else:
                    tokens.append(int(op))
            else:
                tokens.append(op)

        stack = []
        for op in tokens:
            if isinstance(op, int) and stack and stack[-1] == "*":
                stack.pop()
                stack[-1] *= op
            else:
                stack.append(op)

        res = stack[0]

        while len(stack) > 1:
            op = stack[-1]
            stack.pop()
            operator = stack[-1]
            stack.pop()

            if operator == "+":
                res += op
            else:
                assert operator == "-"
                res -= op

        return res

    def addOperators(self, num: str, target: int) -> List[str]:
        res = []

        for comb in product("+-* ", repeat=len(num) - 1):
            # interleave
            operation = [x[i].strip() for i in range(len(num) - 1) for x in [num, comb]]
            operation.append(num[-1])

            operation = "".join(operation)

            if self.has_leading_zeros(operation):
                continue

            if self.eval(operation) == target:
                res.append(operation)

        return res
