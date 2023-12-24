import re
import sys
import random
from sympy import Symbol, solve_poly_system
from sympy.geometry import Point3D, Ray3D, intersection, Point2D, Ray2D

SAMPLE_INPUT = False
TEST_AREA_MIN = 7 if SAMPLE_INPUT else 200000000000000
TEST_AREA_MAX = 27 if SAMPLE_INPUT else 400000000000000
USED_RAYS_FOR_EQUATION = 3  # increase if it doesn't find a unique solution


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break

        res = re.match(
            r"^(-?\d+),\s+(-?\d+),\s+(-?\d+)\s+@\s+(-?\d+),\s+(-?\d+),\s+(-?\d+)$", line
        )
        groups = list(int(x) for x in res.groups())
        coordinate = Point3D(*(int(x) for x in groups[:3]))
        velocity = Point3D(*(int(x) for x in groups[3:]))
        coordinate_b = Point3D(
            coordinate.x + velocity.x,
            coordinate.y + velocity.y,
            coordinate.z + velocity.z,
        )
        yield Ray3D(coordinate, coordinate_b)


def part_1(hailstones: list[Point3D]):
    hailstones = list(
        Ray2D(Point2D(x.p1[0], x.p1[1]), Point2D(x.p2[0], x.p2[1])) for x in hailstones
    )

    res = 0
    for i, a in enumerate(hailstones):
        print(f"{i} / {len(hailstones)}", file=sys.stderr)
        for j, b in enumerate(hailstones):
            if i >= j:
                continue

            inters = intersection(a, b)
            if len(inters) == 0:
                continue

            x, y = inters[0]
            if (
                TEST_AREA_MIN <= x <= TEST_AREA_MAX
                and TEST_AREA_MIN <= y <= TEST_AREA_MAX
            ):
                res += 1

    return res


def part_2(hailstones: list[Point3D]):
    INITIAL_POS = tuple(Symbol(x) for x in ("x0", "y0", "z0"))
    SPEED = tuple(Symbol(x) for x in ("vx0", "vy0", "vz0"))

    # use only a few hailstones for performance reasons
    hailstones = list(hailstones)
    random.seed(1065)
    random.shuffle(hailstones)
    hailstones = hailstones[:USED_RAYS_FOR_EQUATION]

    DELTAS = [Symbol(f"delta{i + 1}") for i, _ in enumerate(hailstones)]

    # X_0 + DELTAS[i] * VX_0 = X_i + DELTAS[i] * VX_i
    # X_0 + DELTAS[i] * (VX_0 - VX_i) - X_i = 0
    equations = [
        (
            INITIAL_POS[coord_idx]
            + DELTAS[i] * (SPEED[coord_idx] - hailstone.direction[coord_idx])
            - hailstone.p1[coord_idx]
        )
        for i, hailstone in enumerate(hailstones)
        for coord_idx in range(3)
    ]

    VARIABLES = (*INITIAL_POS, *SPEED, *DELTAS)

    solution = solve_poly_system(tuple(equations), VARIABLES)[0]
    print(solution, file=sys.stderr)

    return sum(solution[:3])


def main():
    hailstones = list(read_lines())
    print("part_1:", part_1(hailstones))
    print("part_2:", part_2(hailstones))


if __name__ == "__main__":
    main()
