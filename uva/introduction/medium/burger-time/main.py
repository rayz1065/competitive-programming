while True:
    highway_len = int(input().strip())
    if highway_len == 0:
        break
    # R: restaurant, D: drugstore, Z: both
    positions = input().strip()

    last_r, last_d = None, None
    min_dist = len(positions)

    for i, char in enumerate(positions):
        if char == 'Z':
            min_dist = 0
            break

        if char == 'R':
            if last_d is not None:
                min_dist = min(min_dist, i - last_d)
            last_r = i
        elif char == 'D':
            if last_r is not None:
                min_dist = min(min_dist, i - last_r)
            last_d = i

    print(min_dist)
