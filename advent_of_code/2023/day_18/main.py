from collections import namedtuple
from enum import Enum
import re
from itertools import tee

DigInstruction = namedtuple("DigInstruction", ["direction", "distance", "color"])


def pairwise(it):
    a, b = tee(it)
    next(b, None)
    return zip(a, b)


class CardinalDirection(Enum):
    U = "U"
    R = "R"
    D = "D"
    L = "L"


deltas = {
    CardinalDirection.U: (-1, 0),
    CardinalDirection.R: (0, 1),
    CardinalDirection.D: (1, 0),
    CardinalDirection.L: (0, -1),
}
directions_map = {
    "0": CardinalDirection.R,
    "1": CardinalDirection.D,
    "2": CardinalDirection.L,
    "3": CardinalDirection.U,
}


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break

        res = re.match(r"^([URDL])\s+(\d+)\s+\(#(\w+)\)$", line)
        yield DigInstruction(CardinalDirection(res[1]), int(res[2]), res[3])


def get_coords_range(coordinates):
    return [
        (min(x[coord_idx] for x in coordinates), max(x[coord_idx] for x in coordinates))
        for coord_idx in range(2)
    ]


def get_coords(instructions: list[DigInstruction]):
    coordinates = [(0, 0)]
    for instruction in instructions:
        direction, distance, _ = instruction
        r, c = coordinates[-1]
        dr, dc = deltas[direction]
        r, c = r + dr * distance, c + dc * distance
        coordinates.append((r, c))

    coords_range = [
        (min(x[coord_idx] for x in coordinates), max(x[coord_idx] for x in coordinates))
        for coord_idx in range(2)
    ]
    r_min, _ = coords_range[0]
    c_min, _ = coords_range[1]

    # make all coordinates positive
    for i, coordinate in enumerate(coordinates):
        r, c = coordinate
        r -= r_min
        c -= c_min
        coordinates[i] = (r + 1, c + 1)

    return coordinates


def trace_coordinates(coordinates: list[tuple[int, int]]):
    r_range, c_range = get_coords_range(coordinates)
    _, r_max = r_range
    _, c_max = c_range

    grid = [["?" for _ in range(c_max + 2)] for _ in range(r_max + 2)]

    for coordinate_a, coordinate_b in pairwise(coordinates):
        dr = coordinate_b[0] - coordinate_a[0]
        dr //= max(1, abs(dr))
        dc = coordinate_b[1] - coordinate_a[1]
        dc //= max(1, abs(dc))

        r, c = coordinate_a
        while (r, c) != coordinate_b:
            grid[r][c] = "#"
            r, c = r + dr, c + dc

    return grid


def in_range(grid, r, c):
    return 0 <= r < len(grid) and 0 <= c < len(grid[r])


def flood_fill(grid, r, c):
    ff = [(r, c)]
    while len(ff) > 0:
        r, c = ff.pop()

        for dr, dc in deltas.values():
            new_r, new_c = r + dr, c + dc
            if not in_range(grid, new_r, new_c):
                continue

            if grid[new_r][new_c] != "?":
                continue

            grid[new_r][new_c] = "."
            ff.append((new_r, new_c))

    for r, row in enumerate(grid):
        for c, cell in enumerate(row):
            if cell != "?":
                continue

            grid[r][c] = "#"


def print_grid(grid):
    for row in grid:
        print("".join(row))
    print()


def pool_size(grid):
    return sum(cell == "#" for row in grid for cell in row)


def shoelace(coordinates):
    res = 0
    perimeter = 0
    for coordinate_a, coordinate_b in pairwise(coordinates):
        x_i, y_i = coordinate_a
        x_n, y_n = coordinate_b
        res += (y_i + y_n) * (x_i - x_n)
        perimeter += abs(x_n - x_i) + abs(y_n - y_i)

    assert res % 2 == 0 and perimeter % 2 == 0
    return abs(res) // 2 + perimeter // 2 + 1


def instruction_rewrite(instruction: DigInstruction):
    color = instruction.color
    real_distance = int(color[:5], 16)
    real_direction = directions_map[color[-1]]

    return DigInstruction(real_direction, real_distance, "000000")


def part_1(instructions):
    coordinates = get_coords(instructions)
    return shoelace(coordinates)


def part_2(instructions):
    instructions = [instruction_rewrite(instruction) for instruction in instructions]
    coordinates = get_coords(instructions)
    return shoelace(coordinates)


def main():
    instructions = list(read_lines())
    print("part_1:", part_1(instructions))
    print("part_2:", part_2(instructions))


if __name__ == "__main__":
    main()
