from enum import Enum
import itertools

class Dire(Enum):
    N = 0
    NE = 1
    E = 2
    SE = 3
    S = 4
    SW = 5
    W = 6
    NW = 7

DIRE_DELTAS = [
    (-1, 0),
    (-1, 1),
    (0, 1),
    (1, 1),
    (1, 0),
    (1, -1),
    (0, -1),
    (-1, -1),
]

def read_input ():
    elfs = set()
    try:
        for x in itertools.count():
            line = input()
            elfs.update((x, y) for y, cell in enumerate(line) if cell == '#')
    except EOFError:
        pass
    return elfs

def adj (coord: (int, int), dire: Dire):
    x, y = coord
    dx, dy = DIRE_DELTAS[dire.value]
    return x + dx, y + dy

def get_moves_prio (step: int):
    dirs = [Dire.N, Dire.S, Dire.W, Dire.E]
    new_dirs = [dirs[(i + step) % 4] for i in range(4)]
    return new_dirs

def get_move (elfs: set, elf: (int, int), step: int):
    empty_dirs = set(dire for dire in Dire if adj(elf, dire) not in elfs)
    if len(empty_dirs) == 8:
        return elf
    dirs = get_moves_prio(step)
    for dire in dirs:
        adj_a = Dire((dire.value + 1) % 8)
        adj_b = Dire((dire.value + 7) % 8)
        if len(empty_dirs.intersection((dire, adj_a, adj_b))) == 3:
            return adj(elf, dire)
    return elf

def print_grid (elfs: set):
    xs = [x for x, y in elfs]
    ys = [y for x, y in elfs]
    for x in range(min(xs) - 1, max(xs) + 2):
        line = []
        for y in range(min(ys) - 1, max(ys) + 2):
            line.append('#' if (x, y) in elfs else '.')
        print(''.join(line))
    print()

def simulate (elfs: set, step: int):
    proposed = {}
    for elf in elfs:
        move = get_move(elfs, elf, step)
        proposed.setdefault(move, 0)
        proposed[move] += 1
    result = set()
    for elf in elfs:
        move = get_move(elfs, elf, step)
        if proposed[move] == 1:
            result.add(move)
        else:
            result.add(elf)
    return result

def part_1 (elfs):
    for step in range(10):
        elfs = simulate(elfs, step)
    xs = [x for x, y in elfs]
    ys = [y for x, y in elfs]
    return (max(xs) - min(xs) + 1) * (max(ys) - min(ys) + 1) - len(elfs)

def part_2 (elfs):
    for step in itertools.count():
        res = simulate(elfs, step)
        if len(res.symmetric_difference(elfs)) == 0:
            return step + 1
        elfs = res

def main ():
    elfs = read_input()
    print('part_1:', part_1(elfs))
    print('part_2:', part_2(elfs))

if __name__ == '__main__':
    main()
