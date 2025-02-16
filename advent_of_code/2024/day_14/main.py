import re

GRID_ROWS = 7  # 103
GRID_COLS = 11  # 101
GRID_ROWS = 103
GRID_COLS = 101


def read_input():
    res = []
    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        match = re.match(r"p=(\d+),(\d+) v=(-?\d+),(-?\d+)", line)
        res.append(tuple(int(x) for x in match.groups()))
    return res


def simulate(robot):
    x, y, dx, dy = robot
    return (x + dx) % GRID_COLS, (y + dy) % GRID_ROWS, dx, dy


def make_grid(robots):
    res = [[0] * GRID_COLS for _ in range(GRID_ROWS)]
    for x, y, *_ in robots:
        res[y][x] += 1
    return res


def print_grid(robots):
    res = make_grid(robots)
    for row in res:
        print(" ".join(("." if x == 0 else str(x) for x in row)))
    print()


def part_1(robots):
    for t in range(100):
        robots = list(map(simulate, robots))

    quadrant_counts = {}
    for quadrant in filter(None, map(get_quadrant, robots)):
        quadrant_counts.setdefault(quadrant, 0)
        quadrant_counts[quadrant] += 1

    res = 1
    for quadrant in quadrant_counts.values():
        res *= quadrant
    return res


def get_quadrant(robot):
    x, y, *_ = robot
    top = y < GRID_ROWS // 2
    bot = y > GRID_ROWS // 2
    lft = x < GRID_COLS // 2
    rgt = x > GRID_COLS // 2
    if (not top and not bot) or (not lft and not rgt):
        return None
    return (top, lft)


def is_adjacent(a, b):
    return abs(a[0] - b[0]) + abs(a[1] - b[1]) == 1


def part_2(robots):
    t = 0
    while True:
        t += 1
        robots = list(map(simulate, robots))
        score = sum(is_adjacent(x, y) for x in robots for y in robots)
        if score > 1000:
            print(t, score)
            print_grid(robots)
        elif t % 10 == 0:
            print(t)


def main():
    robots = read_input()
    print(part_1(robots))


if __name__ == "__main__":
    main()
