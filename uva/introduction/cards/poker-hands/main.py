VALUES = '23456789TJQKA'

def highest_card (hand):
    values = sorted(VALUES.index(x[0]) for x in hand)
    return tuple(reversed(values))

def is_straight (hand):
    values = sorted((VALUES.index(x[0]) for x in hand))
    prev_value = values[0]
    for value in values[1:]:
        if value != prev_value + 1:
            return False
        prev_value = value
    return True

def is_flush (hand):
    suits = set(x[1] for x in hand)
    return len(suits) == 1

def cards_by_value (hand):
    res = { x: [] for x in VALUES }
    for card in hand:
        res[card[0]].append(card)
    return res

def get_groups (hand, group_size):
    by_value = cards_by_value(hand)
    groups = [cards for cards in by_value.values() if len(cards) == group_size]
    return groups

def score_hand (hand):
    straight = is_straight(hand)
    flush = is_flush(hand)
    pairs = get_groups(hand, 2)
    triples = get_groups(hand, 3)
    quads = get_groups(hand, 4)

    if straight and flush:
        # straight flush
        return 8, highest_card(hand)

    if len(quads) == 1:
        # four of a kind
        return 7, highest_card(quads[0])

    if len(pairs) == 1 and len(triples) == 1:
        # full house
        return 6, highest_card(triples[0])

    if flush:
        # flush
        return 5, highest_card(hand)

    if straight:
        # straight
        return 4, highest_card(hand)

    if len(triples) == 1:
        # three of a kind
        return 3, highest_card(triples[0])

    if len(pairs) == 2:
        # two pairs
        pair_cards = set(pairs[0]).union(pairs[1])
        other_cards = set(hand) - pair_cards
        return 2, (highest_card(pair_cards), highest_card(other_cards))

    if len(pairs) == 1:
        # pair
        other_cards = set(hand) - set(pairs[0])
        return 1, (highest_card(pairs[0]), highest_card(other_cards))

    # high card
    return 0, highest_card(hand)

while True:
    try:
        line = input().strip()
    except EOFError:
        break
    cards = line.split()

    hands = [
        cards[0:5],  # black
        cards[5:10], # white
    ]
    scores = [score_hand(x) for x in hands]

    if scores[0] > scores[1]:
        print('Black wins.')
    elif scores[1] > scores[0]:
        print('White wins.')
    else:
        print('Tie.')
