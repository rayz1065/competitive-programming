def tc (n):
    people = input().strip().split()
    balances = { p: 0 for p in people }
    for _ in range(n):
        p1, spent, _, *gifted_to = input().strip().split()
        spent = int(spent)
        if len(gifted_to) == 0:
            continue
        balances[p1] -= spent // len(gifted_to) * len(gifted_to)
        for p2 in gifted_to:
            balances[p2] += spent // len(gifted_to)
    for p1 in people:
        print(p1, balances[p1])

try:
    is_first = True
    while True:
        n = int(input().strip())
        if not is_first:
            print()
        tc(n)
        is_first = False
except EOFError:
    pass
