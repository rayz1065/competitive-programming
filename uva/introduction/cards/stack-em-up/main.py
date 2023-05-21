t = int(input().strip())
assert input() == ''

def read_shuffle ():
    shuffle = []
    while len(shuffle) < 52:
        shuffle.extend(int(x) for x in input().strip().split())
    return shuffle

for case in range(t):
    n = int(input().strip())
    shuffles = [read_shuffle() for _ in range(n)]
    deck = [
        f'{value} of {suit}'
        for suit in ['Clubs', 'Diamonds', 'Hearts', 'Spades']
        for value in [*'23456789', '10', 'Jack', 'Queen', 'King', 'Ace']
    ]

    while True:
        try:
            line = input().strip()
        except EOFError:
            break
        if line == '':
            break
        shuffle_used = shuffles[int(line) - 1]
        deck_prev = deck.copy()

        for j, i in enumerate(shuffle_used):
            i -= 1
            deck[j] = deck_prev[i]
        assert len(set(deck)) == len(deck)

    if case > 0:
        print()
    print('\n'.join(deck))
