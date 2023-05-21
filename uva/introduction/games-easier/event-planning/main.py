STAY_HOME = 'stay home'

def tc():
    participants, budget, hotels, _ = (int(x) for x in input().strip().split())
    best = None

    for _ in range(hotels):
        price_per_person = int(input().strip())
        free_beds = (int(x) for x in input().strip().split())
        total_cost = price_per_person * participants
        if price_per_person * participants > budget:
            continue

        if max(free_beds) < participants:
            continue

        if best is None or total_cost < best:
            best = total_cost

    print(STAY_HOME if best is None else best)

try:
    while True:
        tc()
except EOFError:
    pass
