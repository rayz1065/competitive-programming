testcases = int(input().strip())

# based on #-oudlers
REQUIRED_SCORES = [56, 51, 41, 36]
CARD_VALUES = { 'king': 9, 'queen': 7, 'knight': 5, 'jack': 3 }

for case in range(1, testcases + 1):
    n = int(input().strip())
    cards = [input().strip() for _ in range(n)]

    oudlers = 0
    score = 0
    for card in cards:
        sections = card.split(' of ')
        if card in ['fool', 'one of trumps', 'twenty-one of trumps']:
            oudlers += 1
            score += 9
        elif sections[0] in CARD_VALUES:
            score += CARD_VALUES[sections[0]]
        else:
            score += 1

    score //= 2

    required_score = REQUIRED_SCORES[oudlers]
    difference = abs(score - required_score)
    if case > 1:
        print()
    print(f'Hand #{case}')
    if score < required_score:
        print(f'Game lost by {difference} point(s).')
    else:
        print(f'Game won by {difference} point(s).')
