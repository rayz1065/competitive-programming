from functools import cache
from collections import namedtuple

Equation = namedtuple("Equation", ["result", "operands"])


def read_input():
    res = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        result, operands = line.split(": ")
        res.append(Equation(int(result), [int(x) for x in operands.split()]))
    return res


@cache
def generate_operations(length, concatenation=False):
    if length == 0:
        return [""]

    res = []
    operators = "+*"
    if concatenation:
        operators += "|"
    for operator in operators:
        for rest in generate_operations(length - 1, concatenation=concatenation):
            res.append(rest + operator)

    return res


def execute_operations(operands, operations):
    res = operands[0]
    for operation, operand in zip(operations, operands[1:]):
        if operation == "+":
            res += operand
        elif operation == "*":
            res *= operand
        elif operation == "|":
            res = int(f"{res}{operand}")
    return res


def check_equation(equation, concatenation=False):
    return any(
        execute_operations(equation.operands, x) == equation.result
        for x in generate_operations(
            len(equation.operands) - 1, concatenation=concatenation
        )
    )


def part_1(equations):
    return sum(x.result for x in equations if check_equation(x))


def part_2(equations):
    return sum(x.result for x in equations if check_equation(x, concatenation=True))


def main():
    equations = read_input()
    print("part1:", part_1(equations))
    print("part2:", part_2(equations))


if __name__ == "__main__":
    main()
