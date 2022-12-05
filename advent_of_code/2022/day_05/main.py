import re

def read_input():
    stacks = []
    while True:
        line = input()
        n = (len(line) + 1) // 4
        if len(stacks) == 0:
            stacks = [[] for _ in range(n)]
        if line[1] == '1':
            break
        res = re.match('^' + ' '.join(r'(\[\w\]|\s{3})' for _ in range(n)) + '$', line)
        assert res is not None
        for i, item in enumerate(res.groups()):
            if item[0] == '[':
                stacks[i].append(item[1])
    assert input() == ''
    stacks = [list(reversed(x)) for x in stacks]
    moves = []
    try:
        while True:
            line = input()
            res = re.match(r'^move (\d+) from (\d+) to (\d+)$', line)
            assert res is not None
            moves.append(tuple(int(x) for x in res.groups()))
    except EOFError:
        pass
    return stacks, moves

def sim_move (stacks, move):
    stacks = list(stacks)
    am, x, y = move
    x -= 1
    y -= 1
    to_move = stacks[x][-am:]
    stacks[x] = stacks[x][:-am]
    stacks[y] = list(stacks[y])
    stacks[y].extend(reversed(to_move))
    return stacks

def sim_move_2 (stacks, move):
    stacks = list(stacks)
    am, x, y = move
    x -= 1
    y -= 1
    to_move = stacks[x][-am:]
    stacks[x] = stacks[x][:-am]
    stacks[y] = list(stacks[y])
    stacks[y].extend(to_move)
    return stacks

def main ():
    stacks, moves = read_input()
    stacks_1 = stacks
    stacks_2 = stacks
    for move in moves:
        stacks_1 = sim_move(stacks_1, move)
        stacks_2 = sim_move_2(stacks_2, move)
    print('part_1:', ''.join(stack[-1] for stack in stacks_1))
    print('part_2:', ''.join(stack[-1] for stack in stacks_2))

if __name__ == '__main__':
    main()
