def read_input ():
    moves = []
    try:
        while True:
            line = input().split()
            moves.append((line[0], int(line[1])))
    except EOFError:
        pass
    return moves

MOVS = {
    'R': (1, 0),
    'D': (0, -1),
    'L': (-1, 0),
    'U': (0, 1),
}

def relax (node, desired_pos):
    # a node chasing the one before
    if abs(desired_pos[0] - node[0]) + abs(desired_pos[1] - node[1]) >= 3:
        # diagonal
        return (
            node[0] + min(1, max(-1, desired_pos[0] - node[0])),
            node[1] + min(1, max(-1, desired_pos[1] - node[1]))
        )
    elif abs(desired_pos[0] - node[0]) == 2:
        return (
            node[0] + min(1, max(-1, desired_pos[0] - node[0])),
            node[1]
        )
    elif abs(desired_pos[1] - node[1]) == 2:
        return (
            node[0],
            node[1] + min(1, max(-1, desired_pos[1] - node[1]))
        )
    return node

def print_map (rope, x_min=0, x_max=7, y_min=0, y_max=7):
    for y in range(y_max, y_min - 1, -1):
        cells = []
        for x in range(x_min, x_max + 1):
            for i, pos in enumerate(rope):
                if pos == (x, y):
                    if i == 0:
                        cells.append('H')
                    else:
                        cells.append(str(i))
                    break
            else:
                cells.append('.')
        print(' '.join(cells))
    print()

def simulate (rope, moves):
    occupied_by_tail = { rope[-1]: True }
    for dire, amount in moves:
        dx, dy = MOVS[dire]
        for _ in range(amount):
            rope[0] = (rope[0][0] + dx, rope[0][1] + dy)
            for i in range(1, len(rope)):
                rope[i] = relax(rope[i], rope[i - 1])
            occupied_by_tail[rope[-1]] = True
    return len(occupied_by_tail)

def main ():
    moves = read_input()
    print('part_1:', simulate([(0, 0)] * 2, moves))
    print('part_2:', simulate([(0, 0)] * 10, moves))
main()
