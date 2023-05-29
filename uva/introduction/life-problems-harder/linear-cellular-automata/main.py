DISHES_COUNT = 40
DAYS_COUNT = 50
STATE_MAP = ' .xW'


def simulate (state, dna):
    new_state = [0] * len(state)
    for i, x in enumerate(state):
        density = x
        if i > 0:
            density += state[i - 1]
        if i + 1 < len(state):
            density += state[i + 1]
        new_state[i] = dna[density]
    return new_state


def state_str (state):
    return ''.join(STATE_MAP[x] for x in state)


def solve (dna):
    state = [0] * DISHES_COUNT
    state[DISHES_COUNT // 2 - 1] = 1

    print(state_str(state))
    for _ in range(DAYS_COUNT - 1):
        state = simulate(state, dna)
        print(state_str(state))

    return state


def main ():
    t = int(input().strip())
    for tc in range(t):
        input()
        dna = [int(x) for x in input().strip().split()]
        solve(dna)

        if tc + 1 < t:
            print()


if __name__ == '__main__':
    main()
