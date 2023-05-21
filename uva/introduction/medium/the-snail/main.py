while True:
    height, climbed_initial, slide_down, fatigue = (int(x) for x in input().strip().split())
    if height == 0:
        break

    day = 1
    y = 0.
    climbed_curr = climbed_initial
    while True:
        y += max(0, climbed_curr)
        if y > height:
            print('success on day', day)
            break

        y -= slide_down

        if y < 0:
            print('failure on day', day)
            break

        climbed_curr -= climbed_initial * fatigue / 100
        day += 1
