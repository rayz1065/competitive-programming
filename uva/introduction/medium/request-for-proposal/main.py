t = 0
while True:
    t += 1
    n, proposals = (int(x) for x in input().strip().split())
    if n == 0:
        break
    _ = [input() for _ in range(n)]

    best_requirements = None
    best_price = None
    best_proposal = None

    for _ in range(proposals):
        proposal = input()
        price, r_met_requirements = input().strip().split()
        price = float(price)
        r_met_requirements = int(r_met_requirements)

        _ = [input() for _ in range(r_met_requirements)]

        if best_proposal is None or r_met_requirements > best_requirements or \
            (r_met_requirements == best_requirements and price < best_price):
            best_requirements = r_met_requirements
            best_price = price
            best_proposal = proposal
    if t > 1:
        print()
    print(f'RFP #{t}')
    print(best_proposal)
