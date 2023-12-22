CARD_NUMBERS = 'A23456789TJQK'


def stack_idx (card):
    return CARD_NUMBERS.index(card[0])


def solve (deck):
    stacks = [[] for _ in range(13)]
    for i, card in enumerate(reversed(deck)):
        stacks[i % len(stacks)].append(card)

    current_idx = -1
    s = 0
    while len(stacks[current_idx]) > 0:
        card = stacks[current_idx].pop()
        s += 1
        current_idx = stack_idx(card)

    return s, card


def read_input ():
    while True:
        line = input().strip()
        if line == '#':
            break
        deck = [line, *(input() for _ in range(3))]
        deck = [x for line in deck for x in line.split()]
        yield deck


def main ():
    for deck in read_input():
        s, card = solve(deck)
        print(f'{str(s).rjust(2, "0")},{card}')


if __name__ == '__main__':
    main()
