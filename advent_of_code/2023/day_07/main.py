from collections import namedtuple

Hand = namedtuple("Hand", ["cards", "bet"])
CARDS = "AKQJT98765432"
HAND_TYPES = {
    "00001": "0.FIVE_OF_A_KIND",
    "10010": "1.FOUR_OF_A_KIND",
    "01100": "2.FULL_HOUSE",
    "20100": "3.THREE_OF_A_KIND",
    "12000": "4.TWO_PAIR",
    "31000": "5.ONE_PAIR",
    "50000": "6.HIGH_CARD",
}


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break

        line = line.split()
        yield Hand(line[0], int(line[1]))


def get_card_freqs(hand: Hand):
    freqs = {}
    for card in hand.cards:
        freqs.setdefault(card, 0)
        freqs[card] += 1

    return freqs


def get_card_strength(card, weak_j=False):
    """Lower is stronger"""
    if weak_j and card == "J":
        return 999

    return CARDS.index(card)


def get_hand_type(hand: Hand):
    freqs = get_card_freqs(hand)
    freq_occurrences = [0] * 6
    for card, freq in freqs.items():
        freq_occurrences[freq] += 1

    freqs_str = "".join(str(x) for x in freq_occurrences[1:])

    return HAND_TYPES[freqs_str]


def get_sort_key_1(hand: Hand):
    hand_type = get_hand_type(hand)

    return (hand_type, *[get_card_strength(x) for x in hand.cards])


def part_1(hands: list[Hand]):
    hands = list(hands)
    hands.sort(key=get_sort_key_1)

    return sum(hand.bet * (idx + 1) for idx, hand in enumerate(reversed(hands)))


def get_hand_type_2(hand: Hand):
    replacements = set(CARDS) - set("J")

    # compute the strongest combination when replacing J with any other card
    return min(
        get_hand_type(Hand(hand.cards.replace("J", replacement), hand.bet))
        for replacement in replacements
    )


def get_sort_key_2(hand: Hand):
    hand_type = get_hand_type_2(hand)

    return (hand_type, *[get_card_strength(x, weak_j=True) for x in hand.cards])


def part_2(hands: list[Hand]):
    hands = list(hands)
    hands.sort(key=get_sort_key_2)

    return sum(hand.bet * (idx + 1) for idx, hand in enumerate(reversed(hands)))


def main():
    hands = list(read_lines())
    print("part_1:", part_1(hands))
    print("part_2:", part_2(hands))


if __name__ == "__main__":
    main()
