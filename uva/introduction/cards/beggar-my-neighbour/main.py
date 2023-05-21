DEALER = 1
NON_DEALER = 2
PLAYER_ARR = [NON_DEALER, DEALER]

def get_penalty (card: str):
    TURNS_BY_CARD = {
        'J': 1,
        'Q': 2,
        'K': 3,
        'A': 4,
    }
    for figure, am in TURNS_BY_CARD.items():
        if card.endswith(figure):
            return am
    return None

while True:
    line = input().strip()
    if line == '#':
        break
    deck = [line, *(input().strip() for _ in range(3))]
    deck = [y for x in deck for y in x.split()]

    hands = [[], []]
    for i, card in enumerate(deck):
        hands[i % 2].append(card)

    turn = NON_DEALER % 2
    missing_cards = None
    table = []
    while True:
        if len(hands[turn]) == 0:
            break
        table.append(hands[turn].pop())

        if (penalty := get_penalty(table[-1])) is not None:
            # dropped a figure, begin countdown
            missing_cards = penalty
            turn = 1 - turn
        elif missing_cards is not None:
            # continue countdown
            missing_cards -= 1
            if missing_cards == 0:
                turn = 1 - turn # player who placed face card takes the deck
                hands[turn].reverse() # place cards face up
                hands[turn].extend(table) # take whole heap
                hands[turn].reverse() # put it back how it was
                table = []
                missing_cards = None
        else:
            # nothing special
            turn = 1 - turn

    print(PLAYER_ARR[1 - turn], str(len(hands[1 - turn])).rjust(2))
