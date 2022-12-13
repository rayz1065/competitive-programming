def read_input ():
    grid = []
    starting = None
    ending = None
    try:
        i = 0
        while True:
            line = input()
            s_idx = line.find('S')
            e_idx = line.find('E')
            if s_idx != -1:
                line = line.replace('S', 'a')
                starting = (i, s_idx)
            if e_idx != -1:
                line = line.replace('E', 'z')
                ending = (i, e_idx)
            grid.append(line)
            i += 1
    except EOFError:
        pass
    return grid, starting, ending

grid = None
MOVS = [(-1, 0), (0, 1), (1, 0), (0, -1)]
INFTY = 2**30

def in_range (x, y):
    return 0 <= x < len(grid) and 0 <= y < len(grid[0])


def adj (x, y):
    for dx, dy in MOVS:
        newx, newy = x + dx, y + dy
        if not in_range(newx, newy):
            continue
        curr_h = ord(grid[x][y])
        new_h = ord(grid[newx][newy])
        if new_h > curr_h + 1:
            continue
        yield newx, newy

def part_1 (starting, ending):
    ff = [starting]
    distances = {}
    distances[starting] = 0
    while len(ff) > 0:
        x, y = ff[0]
        ff = ff[1:] # slow
        for newx, newy in adj(x, y):
            if (newx, newy) not in distances:
                distances[newx, newy] = distances[x, y] + 1
                ff.append((newx, newy))
    if ending not in distances:
        return INFTY
    return distances[ending]

def part_2 (ending):
    s = INFTY
    for x in range(len(grid)):
        for y in range(len(grid[0])):
            if grid[x][y] == 'a':
                s = min(s, part_1((x, y), ending))
    return s

def main ():
    global grid
    grid, starting, ending = read_input()
    print('part_1:', part_1(starting, ending))
    print('part_2:', part_2(ending))

main()
