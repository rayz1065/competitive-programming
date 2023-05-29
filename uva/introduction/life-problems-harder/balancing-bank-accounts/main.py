def main ():
    tc = 0
    while True:
        n, t = (int(x) for x in input().strip().split())
        if (n, t) == (0, 0):
            break

        people = [input().strip() for _ in range(n)]
        transactions = [input().strip().split() for _ in range(t)]

        balances = { x: 0 for x in people }
        for a, b, amount in transactions:
            amount = int(amount)
            balances[a] -= amount
            balances[b] += amount

        negatives = [x for x in people if balances[x] < 0]
        negatives.reverse()
        positives = [x for x in people if balances[x] > 0]

        tc += 1
        print(f'Case #{tc}')

        for person in positives:
            while balances[person] > 0:
                person_b = negatives[-1]
                diff = min(balances[person], -balances[person_b])
                balances[person] -= diff
                balances[person_b] += diff
                if balances[person_b] == 0:
                    negatives.pop()

                print(f'{person} {person_b} {diff}')
        print()


if __name__ == '__main__':
    main()
