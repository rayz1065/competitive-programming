import copy

def rot (state):
    new_state = [[0] * n for _ in range(n)]
    for i, row in enumerate(state):
        for j, c in enumerate(row):
            new_state[j][n - i - 1] = c
    return new_state


def print_state (state):
    for row in state:
        for c in row:
            cell = '#' if c else '.'
            print(cell, end='')
        print()
    print()


def compare_states (state1, state2):
    check1 = sum(sum(row) for row in state1)
    check2 = sum(sum(row) for row in state2)
    if check1 != check2 or check1 == 0:
        return False
    for _ in range(4):
        if all(all(x == y for x, y in zip(row1, row2)) for row1, row2 in zip(state1, state2)):
            return True
        state2 = rot(state2)
    return False


def find_loop ():
    states = [[[0] * n for _ in range(n)]]
    for i, (x, y) in enumerate(operations):
        new_state = copy.deepcopy(states[-1])
        new_state[x][y] = 1 - new_state[x][y]
        for state in states:
            if compare_states(state, new_state):
                return i
        states.append(new_state)
    return None


while True:
    n = int(input().strip())
    if n == 0:
        break
    operations = [
        tuple(int(x) - 1 for x in input().strip().split()[:2])
        for _ in range(2 * n)]

    loop = find_loop()
    players = [2, 1]
    if loop is None:
        print('Draw')
    else:
        print(f'Player {players[loop % 2]} wins on move {loop + 1}')
