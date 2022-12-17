from itertools import tee

EMPTY = 0
ROCK = 1
SAND = 2

def pairwise (it):
    a, b = tee(it)
    next(b)
    return zip(a, b)

def read_input ():
    directions = []
    try:
        while True:
            items = input().split(' -> ')
            directions.append([tuple(int(x) for x in item.split(',')) for item in items])
    except EOFError:
        pass
    return directions

def sign (x):
    return 0 if x == 0 else x // abs(x)

def iter_points (point_a, point_b):
    x, y = point_a
    to_x, to_y = point_b
    dx = sign(to_x - x)
    dy = sign(to_y - y)
    yield x, y
    while x != to_x or y != to_y:
        x += dx
        y += dy
        yield x, y

def draw_map (directions):
    points = {}
    for dire in directions:
        for point_a, point_b in pairwise(dire):
            for x, y in iter_points(point_a, point_b):
                points[x, y] = ROCK
    return points

def drop_sand (grid, x, y):
    while y < 1000:
        if (x, y + 1) not in grid:
            y += 1
        elif (x - 1, y + 1) not in grid:
            x -= 1
            y += 1
        elif (x + 1, y + 1) not in grid:
            x += 1
            y += 1
        else:
            return x, y
    return None

def add_floor (grid):
    max_y = max(point[1] for point in grid)
    for x, y in iter_points((0, max_y + 2), (1000, max_y + 2)):
        grid[x, y] = ROCK

def main ():
    directions = read_input()
    grid = draw_map(directions)
    tot = 0
    while (pos := drop_sand(grid, 500, 0)) is not None:
        x, y = pos
        grid[x, y] = SAND
        tot += 1
    print('part_1:', tot)
    add_floor(grid)
    while (500, 0) not in grid:
        pos = drop_sand(grid, 500, 0)
        x, y = pos
        grid[x, y] = SAND
        tot += 1
    print('part_2:', tot)

if __name__ == '__main__':
    main()
