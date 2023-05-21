while True:
    banks, debentures = (int(x) for x in input().strip().split())
    if banks == 0:
        break
    reserves = [int(x) for x in input().strip().split()]

    for _ in range(debentures):
        debtor, creditor, value = (int(x) for x in input().strip().split())
        reserves[debtor - 1] -= value
        reserves[creditor - 1] += value

    print('S' if min(reserves) >= 0 else 'N')
