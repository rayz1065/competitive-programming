while True:
    n = int(input().strip())
    if n == 0:
        break
    directions = [input().strip() for _ in range(n)]

    top, north, west = 1, 2, 3

    for direction in directions:
        if direction == 'south':
            top, north = north, 7 - top
        elif direction == 'east':
            top, west = west, 7 - top
        elif direction == 'north':
            top, north = 7 - north, top
        else:
            assert direction == 'west'
            top, west = 7 - west, top

    print(top)
