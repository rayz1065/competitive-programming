import sys

free_pile = 1
piles = [0] * 10000

def allocate_pile ():
    global free_pile
    res = free_pile
    free_pile += 1
    return res

def anoi_move (n, pile_from, pile_to):
    global piles
    assert piles[pile_from] >= n, f'moving {n} books from {pile_from} to {pile_to} ' \
                                  f'but {pile_from} only has {piles[pile_from]} books'

    pile_to_prior = piles[pile_to]

    piles[pile_from] -= n
    piles[pile_to] += n
    print(n, pile_from, pile_to)
    return piles[pile_from] < pile_to_prior

def anoi_reverse (n, pile):
    if n == 1:
        return 0
    s = 0
    pile_a = allocate_pile()

    for _ in range(n // 2):
        s += anoi_move(1, pile, pile_a)
    s += anoi_move(n - n // 2, pile, pile_a)
    for _ in range(n - n // 2):
        s += anoi_move(1, pile_a, pile)
    s += anoi_move(n - n // 2, pile, pile_a)
    s += anoi_move(n, pile_a, pile)
    return s

n = int(input().strip())
piles[0] = n
print('total cost:', anoi_reverse(n, 0), file=sys.stderr)
