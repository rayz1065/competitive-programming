DIRECTIONS = 'SWNE'
SIGNS = 'CDSH'
NUMBERS = '23456789TJQKA'

def parse_deck (line):
    return [line[i * 2] + line[i * 2 + 1] for i in range(len(line) // 2)]

def card_key (card):
    return SIGNS.index(card[0]) * len(NUMBERS) + NUMBERS.index(card[1])


while True:
    dealer = input().strip()
    if dealer == '#':
        break
    dealer = DIRECTIONS.index(dealer)
    deck = [x for line in (input(), input())
            for x in parse_deck(line)]

    hands = [[] for _ in range(len(DIRECTIONS))]
    for i, card in enumerate(deck):
        hands[(i + dealer + 1) % len(DIRECTIONS)].append(card)
    for hand in hands:
        hand.sort(key=card_key)

    for direction, hand in zip(DIRECTIONS, hands):
        print(f'{direction}: {" ".join(hand)}')
