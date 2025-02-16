from collections import namedtuple
import re
import numpy as np

COST_A = 3
COST_B = 1
IMPOSSIBLE = 2**64
PART_2_DELTA = 10000000000000

ClawMachine = namedtuple("ClawMachine", ["button_a", "button_b", "Prize"])


def read_input():
    res = []
    first_line = True
    while True:
        try:
            if not first_line:
                input()
            first_line = False
            lines = [input().strip() for _ in range(3)]
        except EOFError:
            break
        coords = (
            [int(z[1]), int(z[2])]
            for z in [
                re.match(r"Button A: X\+(\d+), Y\+(\d+)", lines[0]),
                re.match(r"Button B: X\+(\d+), Y\+(\d+)", lines[1]),
                re.match(r"Prize: X=(\d+), Y=(\d+)", lines[2]),
            ]
        )
        res.append(ClawMachine(*coords))
    return res


def solve(claw, button_a, button_b):
    A = [
        [button_a[0], button_b[0]],
        [button_a[1], button_b[1]],
    ]
    sol = (np.linalg.inv(A) @ np.array(claw)).round().astype(int)

    if not (A @ sol == claw).all():
        return IMPOSSIBLE

    return sol @ np.array([COST_A, COST_B])


def part_1(machines):
    solutions = [solve(claw, a, b) for a, b, claw in machines]
    return sum(x for x in solutions if x < IMPOSSIBLE)


def part_2(machines):
    solutions = [
        solve([x + PART_2_DELTA for x in claw], a, b) for a, b, claw in machines
    ]
    return sum(x for x in solutions if x < IMPOSSIBLE)


def main():
    machines = read_input()
    print("part1:", part_1(machines))
    print("part2:", part_2(machines))


if __name__ == "__main__":
    main()
