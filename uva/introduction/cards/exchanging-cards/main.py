while True:
    n, _ = (int(x) for x in input().strip().split())
    if n == 0:
        break
    cards_1 = set(int(x) for x in input().strip().split())
    cards_2 = set(int(x) for x in input().strip().split())

    exchange_1 = len(cards_1.difference(cards_2))
    exchange_2 = len(cards_2.difference(cards_1))
    print(min(exchange_1, exchange_2))
