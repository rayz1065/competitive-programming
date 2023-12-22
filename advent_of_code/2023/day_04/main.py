import re
from collections import namedtuple

Card = namedtuple("Card", ["card_id", "winning", "numbers"])


def read_lines():
    while True:
        try:
            line = input().strip()
        except EOFError:
            break

        res = re.match(r"Card\s+(\d+): ([\s\d]+)\|([\s\d]+)", line)

        card_id = int(res[1])
        winning = [int(x) for x in res[2].strip().split()]
        numbers = [int(x) for x in res[3].strip().split()]

        yield Card(card_id, winning, numbers)


def compute_score(card: Card):
    found = set(card.winning).intersection(card.numbers)

    if len(found) == 0:
        return 0

    return 2 ** (len(found) - 1)


def part_1(cards: list[Card]):
    return sum(compute_score(x) for x in cards)


def part_2(cards: list[Card]):
    freqs = [1] * len(cards)
    for i, card in enumerate(cards):
        found = set(card.winning).intersection(card.numbers)
        for j in range(len(found)):
            freqs[i + j + 1] += freqs[i]

    return sum(freqs)


def main():
    cards = list(read_lines())
    print("part_1:", part_1(cards))
    print("part_2:", part_2(cards))


if __name__ == "__main__":
    main()
