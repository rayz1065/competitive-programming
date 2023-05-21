testcases = int(input().strip())

for case in range(1, testcases + 1):
    input()
    durations = [int(x) for x in input().strip().split()]

    mile_cost = 0
    juice_cost = 0
    for duration in durations:
        mile_cost += (duration // 30 + 1) * 10
        juice_cost += (duration // 60 + 1) * 15

    best_cost = min(mile_cost, juice_cost)
    res = []
    if mile_cost == best_cost:
        res.append('Mile')
    if juice_cost == best_cost:
        res.append('Juice')
    print(f'Case {case}: {" ".join(res)} {best_cost}')
