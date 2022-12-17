grid = []

ROCKS = [
    [
        '####'
    ], [ 
        '.#.',
        '###',
        '.#.' 
    ], [
        '..#',
        '..#',
        '###' 
    ], [
        '#',
        '#',
        '#',
        '#'
    ], [
        '##',
        '##',
    ],
]
movement_dx = { '>': 1, '<': -1 }
movements = input()
movement_id = 0

PART_1_STEPS = 2022
PART_2_STEPS = 1000000000000

def overlaps (left, bottom, rock_id):
    rock = ROCKS[rock_id]
    for dy, row in enumerate(reversed(rock)):
        y = bottom + dy
        if y < 0:
            # pushed into the floor
            return True
        for dx, block in enumerate(row):
            x = left + dx
            if x < 0 or x >= 7:
                # pushed into a wall
                return True
            if block == '#' and y < len(grid) and grid[y][x] != '.':
                # pushed into some other block
                return True
    return False

def place_rock (left, bottom, rock_id):
    rock = ROCKS[rock_id]
    for dy, row in enumerate(reversed(rock)):
        y = bottom + dy
        assert y >= 0
        while y >= len(grid):
            # extend the grid
            grid.append(['.' for _ in range(7)])
        for dx, block in enumerate(row):
            # place each row in the grid
            x = left + dx
            assert 0 <= x < 7
            if block == '#':
                assert grid[y][x] == '.'
                grid[y][x] = '#'

def add_falling_rock (rock_id):
    global movement_id
    left = 2
    bottom = len(grid) + 3
    while True:
        # pushed by the current
        left += movement_dx[movements[movement_id]]
        if overlaps(left, bottom, rock_id):
            left -= movement_dx[movements[movement_id]]
        movement_id = (movement_id + 1) % len(movements)
        # falls by 1
        bottom -= 1
        if overlaps(left, bottom, rock_id):
            # comes to rest
            bottom += 1
            return left, bottom

def print_grid ():
    for i, row in enumerate(reversed(grid)):
        WALL = '|'
        print(WALL, ''.join(row), WALL, sep='')
    print('+', '-' * 7, '+', sep='')

def main ():
    global movement_id
    i = 0
    visited = {}
    periodicity = None
    period_h = None
    part_1 = None
    while part_1 is None or periodicity is None:
        left, bottom = add_falling_rock(i % len(ROCKS))
        if i % len(ROCKS) == 0 and 1 <= left <= 5:
            # this may fail in case the line block falls through a gap
            # but that's very likely to happen consistently
            if (left, movement_id) in visited:
                prev_i, prev_h = visited[left, movement_id]
                periodicity = i - prev_i
                period_h = len(grid) - prev_h
            visited[left, movement_id] = (i, len(grid))
        place_rock(left, bottom, i % len(ROCKS))
        i += 1
        if i == PART_1_STEPS:
            part_1 = len(grid)
    skipped_rounds = (PART_2_STEPS - i) // periodicity
    i += skipped_rounds * periodicity
    while i < PART_2_STEPS:
        left, bottom = add_falling_rock(i % len(ROCKS))
        place_rock(left, bottom, i % len(ROCKS))
        i += 1
    total_height = len(grid) + skipped_rounds * period_h
    print('part_1:', part_1)
    print('part_2:', total_height)

if __name__ == '__main__':
    main()
