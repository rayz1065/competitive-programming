def main():
    n, k = (int(x) for x in input().strip().split())
    cards = [int(x) for x in input().strip().split()]
    highest_cost = max(cards)
    cards_sum = sum(cards)

    res = 0
    hand = [cards[0], cards[1]]
    i = 2
    while highest_cost not in hand and k:
        card = min(hand)
        res += card
        hand.remove(card)
        cards.append(card)
        hand.append(cards[i])
        k -= 1
        i += 1

    increments = k // (n - 1)
    k -= increments * (n - 1)
    res += increments * (cards_sum - highest_cost)

    while k:
        card = min(hand)
        res += card
        hand.remove(card)
        cards.append(card)
        hand.append(cards[i])
        k -= 1
        i += 1

    print(res)


if __name__ == "__main__":
    main()
