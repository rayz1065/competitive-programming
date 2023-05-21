while True:
    n, _ = (int(x) for x in input().strip().split())
    if n == 0:
        break
    balls = [int(x) for x in input().strip().split()]

    found = set()
    for a in balls:
        for b in balls:
            if a < b:
                found.add(b - a)

    print('Y' if len(found) == n else 'N')
